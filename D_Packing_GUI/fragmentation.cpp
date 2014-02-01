#include "mainpack.h"

#include <math.h>

using namespace std;

void Packing::figureFragmentation()
{
    FigureList quantFragmentation;
    FigureList maxFragmentation;
    DoubleList x, y;

    for (int i = 0; i < source.count(); ++i)
    {
        this->gridNodes(source[i]);
        x = xGrid[i];
        y = yGrid[i];
        quantFragmentation.append(this->quantumFragmentation(x, y, source[i]));
        maxFragmentation.append(this->maxFigure(x, y, copyGrid(grids[i], x.count() - 1, y.count() - 1)));
    }
    data.append(source);
    data.append(quantFragmentation);
    data.append(maxFragmentation);
}

void Packing::gridNodes(Figure f)
{
    DoubleList x;
    DoubleList y;
    double xl, xr, yt, yb;
    for (int i = 0; i < f.count(); ++i)
    {
        xl = f[i].x();
        xr = xl + f[i].width();
        yt = f[i].y();
        yb = yt + f[i].height();

        if (!i)
        {
            x << xl << xr;
            y << yt << yb;
            continue;
        }

        insertSorting(&x, xl);
        insertSorting(&x, xr);
        insertSorting(&y, yt);
        insertSorting(&y, yb);
    }
    xGrid.append(x);
    yGrid.append(y);
}

Figure Packing::quantumFragmentation(DoubleList x, DoubleList y, Figure f)
{
    double w, h;
    Figure res;
    QRectF rectSource, rectGrid;
    BoolGrid square = new bool* [x.count() - 1];
    for (int i = 0; i < x.count() - 1; ++i)
    {
        square[i] = new bool [y.count() - 1];
        memset(square[i], false, sizeof(bool) * (y.count() - 1));
        for (int j = 0; j < y.count() - 1; ++j)
        {
            w = x[i + 1] - x[i];
            h = y[j + 1] - y[j];
            rectGrid = QRectF(x[i], y[j], w, h);
            for (int k = 0; k < f.count(); ++k)
            {
                rectSource = f[k];
                if (aContainB(rectSource, rectGrid))//rectSource.contains(rectGrid))
                {
                    res.append(rectGrid);
                    square[i][j] = true;
                    break;
                }
            }
        }
    }
    grids.append(square);
    return res;
}

Figure Packing::maxFigure(DoubleList x, DoubleList y, BoolGrid grid)
{
    Figure res;

    int xSqrCnt = x.count() - 1;
    int ySqrCnt = y.count() - 1;
    typedef QPair<QPoint, QPoint> VertexPairs;
    typedef QList<VertexPairs> Squares;
    Squares sq;
    int l, t, r, b;

    // Выбор всех прямоугольников
    for (l = 0; l < xSqrCnt; ++l)
    {
        for (t = 0; t < ySqrCnt; ++t)
        {
            for (r = xSqrCnt; r > l; --r)
            {
                for (b = ySqrCnt; b > t; --b)
                {
                    if (grid[l][t])
                    {
                        sq.append(VertexPairs(QPoint(l, t), QPoint(r, b)));
                    }
                }
            }
        }
    }

    // сортировка по площади
    QPoint lt, rb;
    double s1, s2;
    for (int i = 0; i < sq.count(); ++i)
    {
        for (int j = i + 1; j < sq.count(); ++j)
        {
            lt = sq[i].first;
            rb = sq[i].second;
            l = lt.x();
            t = lt.y();
            r = rb.x();
            b = rb.y();
            s1 = (x[r] - x[l]) * (y[b] - y[t]);

            lt = sq[j].first;
            rb = sq[j].second;
            l = lt.x();
            t = lt.y();
            r = rb.x();
            b = rb.y();
            s2 = (x[r] - x[l]) * (y[b] - y[t]);

            if (s1 < s2)
            {
                sq.swap(i, j);
            }
        }
    }

    // Выбор прямоугольников, принадлежащих фигуре и разбиение
    int iter = 1;
    bool isAdding;
    int **gridSep = new int* [xSqrCnt];
    for (int i = 0; i < xSqrCnt; ++i)
    {
        gridSep[i] = new int [ySqrCnt];
        memset(gridSep[i], 0, sizeof(int) * ySqrCnt);
    }
    for (int k = 0; k < sq.count(); ++k)
    {
        lt = sq[k].first;
        rb = sq[k].second;
        l = lt.x();
        t = lt.y();
        r = rb.x();
        b = rb.y();

        isAdding = true;
        for (int i = l; i < r; ++i)
        {
            for (int j = t; j < b; ++j)
            {
                isAdding = isAdding && grid[i][j];
            }
        }

        if (isAdding)
        {
            for (int i = l; i < r; ++i)
            {
                for (int j = t; j < b; ++j)
                {
                    grid[i][j] = false;
                    gridSep[i][j] = iter;
                }
            }
            ++iter;
            res.append(QRectF(x[l], y[t], x[r] - x[l], y[b] - y[t]));
        }
    }

    for (int i = 0; i < xSqrCnt; ++i)
    {
        delete gridSep[i];
    }
    delete gridSep;

    return res;
}

void Packing::figuresRect()
{
    for (int i = 0; i < fCount; ++i)
    {
        figuresBound.append(rectByFigure(source[i]));
    }
}
