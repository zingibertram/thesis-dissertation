#include "packing.h"

FigurePacking::FigurePacking(FigureList fs, BoolGridList gs, DoubleGrid x, DoubleGrid y, double w, double l)
{
    source = fs;
    grids = gs;
    xGrid = x;
    yGrid = y;
    stripWidth = w;
    stripLength = l;
    count = fs.count();
}

//void FigurePacking::figureCortage(BoolGrid grid, DoubleList x, DoubleList y)
//{
//    Cortage cortx;
//    for (int i = 0; i < x.count() - 1; ++i)
//    {
//        double xi = x[i + 1];
//        double h = 0.0;
//        for (int j = 0; j < y.count() - 1; ++j)
//        {
//            if (grid[i][j])
//            {
//                h += y[j + 1] - y[j];
//            }
//        }
//        cortx.append(TupleCoordLength(xi, h));
//    }
//    xCortage.append(cortx);

//    Cortage corty;
//    for (int i = 0; i < y.count() - 1; ++i)
//    {
//        double w = 0.0;
//        double yi = y[i + 1];
//        for (int j = 0; j < x.count() - 1; ++j)
//        {
//            if (grid[j][i])
//            {
//                w += x[j + 1] - x[j];
//            }
//        }
//        corty.append(TupleCoordLength(yi, w));
//    }
//    yCortage.append(corty);
//}

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
}

void FigurePacking::packCortage()
{
    Cortage xres = xCortage[0];
    Cortage yres = yCortage[0];
    xPos.append(0.0);
    yPos.append(0.0);

    Cortage newx, newy,  xcor, ycor, newxres, newyres;
    DoubleList cortXCoords, cortYCoords;
    double figx, figy;
    for (int i = 1; i < count; ++i)
    {
        xcor = xCortage[i];
        ycor = yCortage[i];
        cortXCoords = getCortageCoords(xres);
        cortYCoords = getCortageCoords(yres);

        int j = -1;
        int k = -1;
        int num = 0;
        do
        {
            if (j < cortXCoords.count())
            {
                figx = -1.0;
                for (++j; j < cortXCoords.count(); ++j)
                {
                    if (j)
                    {
                        newx = shiftCortage(xcor, cortXCoords[j]);
                    }
                    else
                    {
                        newx = xcor;
                    }
                    newxres = sum(xres, newx);
                    if (checkSize(newxres, stripWidth, stripLength))
                    {
                        figx = cortXCoords[j];
                        break;
                    }
                }
            }

            figy = -1.0;
            for (k = cortYCoords.count() - 1; k >= 0; --k)
            {
                if (k)
                {
                    newy = shiftCortage(ycor, cortYCoords[k]);
                }
                else
                {
                    newy = ycor;
                }
                newyres = sum(yres, newy);
                if (checkSize(newyres, stripLength, stripWidth))
                {
                    figy = cortYCoords[k];
                    break;
                }
            }

            ++num;
        } while (!checkOverlap(figx, figy, i)
                 && (j < cortXCoords.count() || k >= 0));
        if (checkOverlap(figx, figy, i))
        {
            xPos.append(figx);
            yPos.append(figy);
            xres = newxres;
            yres = newyres;
        }
        if (figx < 0.0 || figy < 0.0)
        {
            xPos.append(-1.0);
            yPos.append(-1.0);
        }
    }
}

DoubleList FigurePacking::getCortageCoords(Cortage cort)
{
    DoubleList res;
    res.append(0.0);
    for (int i = 0; i < cort.count(); ++i)
    {
        res.append(cort[i].first);
    }
    return res;
}

Cortage FigurePacking::shiftCortage(Cortage c, double shift)
{
    Cortage res;
    res.append(TupleCoordLength(shift, 0.0));
    for (int i = 0; i < c.count(); ++i)
    {
        res.append(TupleCoordLength(shift + c[i].first, c[i].second));
    }
    return res;
}

Cortage FigurePacking::sum(Cortage c1, Cortage c2)
{
    Cortage res;

    int cnt1 = c1.count();
    int cnt2 = c2.count();
    if (!cnt1 && !cnt2)
    {
        return res;
    }
    else
    {
        if (cnt1 && !cnt2)
        {
            return c1;
        }
        if (!cnt1 && cnt2)
        {
            return c2;
        }
    }

    Cortage insc1 = insertCortage(c1, c2);
    Cortage insc2 = insertCortage(c2, c1);
    for (int i = 0; i < insc1.count(); ++i)
    {
        res.append(TupleCoordLength(insc1[i].first, insc1[i].second + insc2[i].second));
    }

    return res;
}

Cortage FigurePacking::insertCortage(Cortage src, Cortage ins)
{
    Cortage res(src);

    // ������� ��������
    int cmp;
    for (int i = 0; i < ins.count(); ++i)
    {
        for (int j = 0; j < res.count(); ++j)
        {
            cmp = tupleCompare(ins[i], res[j]);
            if (!cmp)
            {
                break;
            }
            else
            {
                if (cmp == -1)
                {
                    res.insert(j, TupleCoordLength(ins[i].first, res[j].second));//0.0));
                    break;
                }
                else
                {
                    if (j == res.count() - 1)
                    {
                        res.insert(j + 1, TupleCoordLength(ins[i].first, 0.0));
                        break;
                    }
                }
            }
        }
    }

    return res;
}

// ����������� �������
bool FigurePacking::checkSize(Cortage x, double w, double l)
{
    TupleCoordLength tx = x[x.count() - 1];

    bool bl = (epsCompare(tx.first, l) < 1);

    double maxw = 0.0;
    for (int i = 0; i < x.count(); ++i)
    {
        if (epsCompare(x[i].second, maxw) == 1)
        {
            maxw = x[i].second;
        }
    }
    bool bw = (epsCompare(maxw, w) < 1);

    return bw && bl;
}

// ����������� �������
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

    for (int i = 0; i < cnt; ++i)
    {
        f = source[i];
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
                xk = rk.x() + xPos[i];
                yk = rk.y() + yPos[i];
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
                if (epsCompare(s, w))
                {
                    w = s;
                }

                s = r.y() + r.height() + yPos[i];
                if (epsCompare(s, h))
                {
                    h = s;
                }
            }
        }
    }
    return w * h;
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
    this->figuresToCortage();
    this->packCortage();
}
