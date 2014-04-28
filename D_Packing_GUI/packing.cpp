#include "packing.h"

#include <QDebug>
#include <QTime>
#include <math.h>
#include <QApplication>

FigurePacking::FigurePacking()
{
    ;
}

FigurePacking::FigurePacking(FigureList fs,
                             BoolGridList gs,
                             DoubleGrid x, DoubleGrid y,
                             double w, double l,
                             Figure bound)
{
    source = fs;
    grids = gs;
    xGrid = x;
    yGrid = y;
    stripWidth = w;
    stripLength = l;
    count = fs.count();
    figuresBound = bound;
}

Cortage FigurePacking::figureToCortage(BoolGrid grid, DoubleList coor, DoubleList width, bool xy)
{
    Cortage cort;
    double coord, w;
    int fidx, sidx;

    for (int i = 0; i < coor.count() - 1; ++i)
    {
        coord = coor[i + 1];
        w = 0.0;
        for (int j = 0; j < width.count() - 1; ++j)
        {
            if (xy)
            {
                fidx = i;
                sidx = j;
            }
            else
            {
                fidx = j;
                sidx = i;
            }
            if (grid[fidx][sidx])
            {
                w += width[j + 1] - width[j];
            }
        }
        cort.append(TupleCoordLength(coord, w));
    }
    return cort;
}

void FigurePacking::figuresToCortage()
{
    for (int i = 0; i < count; ++i)
    {
        xCortage.append(this->figureToCortage(grids[i], xGrid[i], yGrid[i], true));
        yCortage.append(this->figureToCortage(grids[i], yGrid[i], xGrid[i], false));
    }
    grids = BoolGridList();
    xGrid = DoubleGrid();
    yGrid = DoubleGrid();
}

void FigurePacking::packCortage()
{
    Cortage xres = xCortage[0];
    Cortage yres = yCortage[0];
    xPos.append(0.0);
    yPos.append(0.0);

    Cortage newx, newy,
            xcor, ycor,
            newxres, newyres,
            localXRes, localYRes;
    DoubleList cortXCoords, cortYCoords;
    double figx, figy;
    double localXCoords, localYCoords;
    int j, k;
    for (int i = 1; i < count; ++i)
    {
        xcor = xCortage[i];
        ycor = yCortage[i];

        localXCoords = POS_INF;

        cortXCoords = this->getCortageCoords(xres, xcor);
        cortYCoords = this->getCortageCoords(yres, ycor);

        figx = -1.0;
        for (j = 0; j < cortXCoords.count(); ++j)
        {
            if (j)
            {
                this->shiftCortage(&newx, cortXCoords[j], cortXCoords[j - 1]);
            }
            else
            {
                newx = xcor;
            }
            newxres = this->sum(&xres, &newx);
            if (this->checkSize(&newxres, stripWidth, stripLength))
            {
                figx = cortXCoords[j];

                figy = -1.0;
                for (k = 0; k <  cortYCoords.count(); ++k)
                {
                    QApplication::processEvents();
                    if (isCanceled)
                    {
                        return;
                    }

                    if (k)
                    {
                        this->shiftCortage(&newy, cortYCoords[k], cortYCoords[k - 1]);
                    }
                    else
                    {
                        newy = ycor;
                    }
                    newyres = this->sum(&yres, &newy);
                    if (this->checkSize(&newyres, stripLength, stripWidth))
                    {
                        figy = cortYCoords[k];

                        if (this->checkOverlap(figx, figy, i)
                            && (localXCoords >= POS_INF - eps || figx < localXCoords))
                        {
                            localXCoords = figx;
                            localYCoords = figy;
                            localXRes = newxres;
                            localYRes = newyres;
                        }
                    }
                }
            }
        }

        if (this->checkOverlap(localXCoords, localYCoords, i))
        {
            xPos << localXCoords;
            yPos << localYCoords;
            xres = localXRes;
            yres = localYRes;
        }
        if (localXCoords < 0.0 || localYCoords < 0.0)
        {
            xPos << -1.0;
            yPos << -1.0;
        }
    }
}

DoubleList FigurePacking::getTightCoords(Cortage src, Cortage ins)
{
    DoubleList res;

    double buf;
    for (int i = 0; i < src.count(); ++ i)
    {
        for (int j = 0; j < ins.count(); ++ j)
        {
            buf = src[i].first - ins[j].first;
            if (buf > eps)
            {
                res.append(buf);
            }
            else
            {
                break;
            }
        }
    }

    return res;
}

DoubleList FigurePacking::getCortageCoords(Cortage src, Cortage ins)
{
    DoubleList res;
    res.append(0.0);
    res.append(this->getTightCoords(src, ins));
    for (int i = 0; i < src.count(); ++i)
    {
        res.append(src[i].first);
    }
    qSort(res);
    for (int i = 0; i < res.count() - 1; ++i)
    {
        if (!epsCompare(res[i], res[i + 1]))
        {
            res.removeAt(i + 1);
            --i;
        }
    }
    return res;
}

void FigurePacking::shiftCortage(Cortage *c, double shift, double prevShift)
{
    if ((*c)[0].second == 0)
    {
        c->removeAt(0);
    }
    c->insert(0, TupleCoordLength(shift, 0.0));
    shift -= prevShift;
    for (int i = 1; i < c->count(); ++i)
    {
        (*c)[i].first += shift;
    }
}

Cortage FigurePacking::sum(Cortage *c1, Cortage *c2)
{
    Cortage res;

    int cnt1 = c1->count();
    int cnt2 = c2->count();
    if (!cnt1 && !cnt2)
    {
        return res;
    }
    else
    {
        if (cnt1 && !cnt2)
        {
            return *c1;
        }
        if (!cnt1 && cnt2)
        {
            return *c2;
        }
    }

    Cortage* insc1 = this->insertCortage(c1, c2);
    Cortage* insc2 = this->insertCortage(c2, c1);
    for (int i = 0; i < insc1->count(); ++i)
    {
        res.append(TupleCoordLength((*insc1)[i].first,(* insc1)[i].second + (*insc2)[i].second));
    }
    delete insc1;
    delete insc2;

    return res;
}

Cortage* FigurePacking::insertCortage(Cortage *src, Cortage *ins)
{
    Cortage *res = new Cortage(*src);

    // сделать линейной
    int cmp;
    int j = 0;
    for (int i = 0; i < ins->count(); ++i)
    {
        for (; j < res->count(); ++j)
        {
            cmp = tupleCompare((*ins)[i], (*res)[j]);
            if (!cmp)
            {
                break;
            }
            else
            {
                if (cmp == -1)
                {
                    res->insert(j, TupleCoordLength((*ins)[i].first, (*res)[j].second));
                    ++j;
                    break;
                }
                else
                {
                    if (j == res->count() - 1)
                    {
                        res->insert(j + 1, TupleCoordLength((*ins)[i].first, 0.0));
                        ++j;
                        break;
                    }
                }
            }
        }
    }

    return res;
}

// необходимое условие
bool FigurePacking::checkSize(Cortage *x, double w, double l)
{
    TupleCoordLength tx = (*x)[x->count() - 1];

    bool bl = (epsCompare(tx.first, l) < 1);

    double maxw = 0.0;
    for (int i = 0; i < x->count(); ++i)
    {
        if (epsCompare((*x)[i].second, maxw) == 1)
        {
            maxw = (*x)[i].second;
        }
    }
    bool bw = (epsCompare(maxw, w) < 1);

    return bw && bl;
}

// достаточное условие
bool FigurePacking::checkOverlap(double nx, double ny, int cnt)
{
    if (nx < 0.0 || ny < 0.0)
    {
        return false;
    }
    Figure checkingFigure = source[cnt];
    Figure f;

    bool bxj, bxk, byj, byk;

    double xj, wj, yj, hj;
    double xk, wk, yk, hk;

    QRectF rj, rk;

    double fx, fy;

    for (int i = 0; i < cnt; ++i)
    {
        f = source[i];
        fx = xPos[i];
        fy = yPos[i];
        if (!(nx + figuresBound[cnt].width() <= fx
              || fx + figuresBound[i].width() <= nx
              || ny + figuresBound[cnt].height() <= fy
              || fy + figuresBound[i].height() <= ny))
        {
            for (int j = 0; j < checkingFigure.count(); ++j)
            {
                rj = checkingFigure[j];
                xj = rj.x() + nx;
                yj = rj.y() + ny;
                wj = rj.width();
                hj = rj.height();
                for (int k = 0; k < f.count(); ++k)
                {
                    rk = f[k];
                    xk = rk.x() + fx;
                    yk = rk.y() + fy;
                    wk = rk.width();
                    hk = rk.height();

                    bxj = (epsCompare(xj, xk + wk) > -1);
                    bxk = (epsCompare(xk, xj + wj) > -1);
                    byj = (epsCompare(yj, yk + hk) > -1);
                    byk = (epsCompare(yk, yj + hj) > -1);

                    if (!(bxj || bxk || byj || byk))
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

double FigurePacking::squarePacking()
{
    double w = 0.0;
    double h = 0.0;
    Figure f;
    QRectF r;
    double s;
    for (int i = 0; i < count; ++i)
    {
        if (xPos[i] >= 0.0 && yPos[i] >= 0.0)
        {
            f = source[i];
            for (int j = 0; j < f.count(); ++j)
            {
                r = f[j];

                s = r.x() + r.width() + xPos[i];
                if (epsCompare(s, w) != -1)
                {
                    w = s;
                }

                s = r.y() + r.height() + yPos[i];
                if (epsCompare(s, h) != -1)
                {
                    h = s;
                }
            }
        }
    }
    return w * stripWidth;
}

DoubleList FigurePacking::xPositions()
{
    return xPos;
}

DoubleList FigurePacking::yPositions()
{
    return yPos;
}

void FigurePacking::pack()
{
    QTime t;
    this->figuresToCortage();
    qDebug() << "Start packing";
    t.start();
    this->packCortage();
    int ms = t.elapsed();
    qDebug() << "Working time" << ms;
}

FigureList FigurePacking::xCortToFig()
{
    double prev;
    FigureList res;
    Figure f;
    for (int i = 0; i < xCortage.count(); ++i)
    {
        f.clear();
        prev = 0.0;
        for (int j = 0; j < xCortage[i].count(); ++j)
        {
            f << QRectF(prev, 0.0, xCortage[i][j].first - prev, xCortage[i][j].second);
            prev = xCortage[i][j].first;
        }
        res << f;
    }
    return res;
}

FigureList FigurePacking::yCortToFig()
{
    double prev;
    FigureList res;
    Figure f;
    for (int i = 0; i < yCortage.count(); ++i)
    {
        f.clear();
        prev = 0.0;
        for (int j = 0; j < yCortage[i].count(); ++j)
        {
            f << QRectF(prev, 0.0, yCortage[i][j].first - prev, yCortage[i][j].second);
            prev = yCortage[i][j].first;
        }
        res << f;
    }
    return res;
}
