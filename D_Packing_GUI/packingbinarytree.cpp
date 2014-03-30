#include "packing.h"

#include <QDebug>
#include <QTime>
#include <math.h>

void FigurePacking::packTreeLeafPair(int l, int r)
{
    Cortage xcor, ycor,
            newxres, newyres,
            localXRes, localYRes;
    DoubleList cortXCoords, cortYCoords;
    double figx, figy,
           localXCoords, localYCoords;

    xcor = xCortage[r];

    localXCoords = POS_INF;

    cortXCoords = this->getCortageCoords(xCortage[l], xcor);
    cortYCoords = this->getCortageCoords(yCortage[l], ycor);

    qDebug() << "Cort count " << cortXCoords.count() << " " << cortYCoords.count();

    figx = -1.0;
    int k;
    for (int j = 0; j < cortXCoords.count(); ++j)
    {
        if (j)
        {
            this->shiftCortage(&xcor, cortXCoords[j], cortXCoords[j - 1]);
        }
        newxres = this->sum(&xCortage[l], &xcor);
        if (this->checkSize(&newxres, stripWidth, stripLength))
        {
            figx = cortXCoords[j];

            ycor = yCortage[r];
            figy = -1.0;
            for (k = 0; k <  cortYCoords.count(); ++k)
            {
                if (k)
                {
                    this->shiftCortage(&ycor, cortYCoords[k], cortYCoords[k - 1]);
                }
                newyres = this->sum(&yCortage[l], &ycor);
                if (this->checkSize(&newyres, stripLength, stripWidth))
                {
                    figy = cortYCoords[k];

                    if (this->checkOverlapPair(l, r, figx, figy)
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

    this->sumFigure(l, r, localXCoords, localYCoords, localXRes, localYRes);
}

void FigurePacking::sumFigure(int l, int r, double x, double y, Cortage cx, Cortage cy)
{
    if (this->checkOverlapPair(l, r, x, y))
    {
        for (int i = 0; i < source[r].count(); ++i)
        {
            source[r][i].setX(x + source[r][i].x());
            source[r][i].setY(y + source[r][i].y());
            source[l] << source[r];
        }

        figuresBound[l].setWidth(std::max(figuresBound[l].width(), x + figuresBound[r].width()));
        figuresBound[l].setHeight(std::max(figuresBound[l].height(), x + figuresBound[r].height()));

        xCortage[l] = cx;
        yCortage[l] = cy;

        for (int i = 0; i < rectLeafs[r].count(); ++i)
        {
            xPos[rectLeafs[r][i]] += x;
            yPos[rectLeafs[r][i]] += y;
        }
        rectLeafs[l].append(rectLeafs[r]);
    }

    source.removeAt(r);
    figuresBound.removeAt(r);
    xCortage.removeAt(r);
    yCortage.removeAt(r);
    rectLeafs.removeAt(r);
}

bool FigurePacking::checkOverlapPair(int l, int r, double nx, double ny)
{
    if (nx < 0.0 || ny < 0.0)
    {
        return false;
    }

    Figure lfig = source[l];
    Figure rfig = source[r];

    bool bxj, bxk, byj, byk;

    double xj, wj, yj, hj;
    double xk, wk, yk, hk;

    lfig = source[l];
    if (!(nx + figuresBound[r].width() <= 0
          || figuresBound[l].width() <= nx
          || ny + figuresBound[r].height() <= 0
          || figuresBound[l].height() <= ny))
    {
        for (int j = 0; j < rfig.count(); ++j)
        {
            xj = rfig[j].x() + nx;
            yj = rfig[j].y() + ny;
            wj = rfig[j].width();
            hj = rfig[j].height();
            for (int k = 0; k < lfig.count(); ++k)
            {
                xk = lfig[k].x();
                yk = lfig[k].y();
                wk = lfig[k].width();
                hk = lfig[k].height();

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

void FigurePacking::packCortageBinaryTree()
{
    int i;
    int k = 0;
    while (source.count() > 1)
    {
        for (i = 0; i < source.count() - 1; ++i)
        {
            this->packTreeLeafPair(i, i + 1);
        }
        qDebug() << "Calculated level - " << k;
        ++k;
    }
}

void FigurePacking::packBinaryTree()
{
    QList<int> ls;
    ls << 0;
    for (int i = 0; i < count; ++i)
    {
        xPos << 0.0;
        yPos << 0.0;
        ls[0] = i;
        rectLeafs << ls;
    }

    this->figuresToCortage();
    qDebug() << "Start packing binary tree";

    QTime t;
    t.start();

    sourceBin = source;
    this->packCortageBinaryTree();
    source = sourceBin;

    int ms = t.elapsed();
    qDebug() << "Working time" << ms;
}
