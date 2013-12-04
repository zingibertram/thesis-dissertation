#include "fragmentation.h"

#include <math.h>
#include <iostream>

using namespace std;

FigureVariantList figureFragmentation(FigureList figure)
{
    FigureVariantList res;
    FigureList quantFragmentation;
    FigureList maxFragmentation;
    Quantum q;
    DoubleList x, y;

    for (int i = 0; i < figure.count(); ++i)
    {
        ListXY xy = gridNodes(figure[i]);
        x = xy.first;
        y = xy.second;
        q = quantumFragmentation(xy, figure[i]);

//        QRectF back(0, 0, x[x.count() - 1], y[y.count() - 1]);
//        showRect(q.first, back);
        printFigureGrid(q.second, x.count() - 1, y.count() - 1);

        quantFragmentation.append(q.first);
        maxFragmentation.append(maxFigure(Field(xy, q.second)));

//        deleteGrid(q.second, x.count());
    }
    res.append(figure);
    res.append(quantFragmentation);
    res.append(maxFragmentation);
    return res;
}

void insertSorting(DoubleList *l, double d)
{
    double li;
    for (int i = 0; i < l->count(); i++)
    {
        li = l->operator [](i);
        if (fabs(li - d) <= eps)
        {
            return;
        }

        if (li > d /*+ eps*/)
        {
            l->insert(i, d);
            break;
        }
        else
        {
            if (i == l->count() - 1)
            {
                l->insert(i + 1, d);
                break;
            }
        }
    }
}

ListXY gridNodes(Figure f)
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
//    for (int i = 0; i < x.count(); ++i)
//    {
//        cout << x[i] << " ";
//    }
//    cout << endl;
//    for (int i = 0; i < y.count(); ++i)
//    {
//        cout << y[i] << " ";
//    }
//    cout << endl;
    return ListXY(x, y);
}

QRectF rectByLines(double l, double r, double t, double b)
{
    return QRectF(l, t, r - l, b - t);
}

Quantum quantumFragmentation(ListXY xy, Figure f)
{
    DoubleList x = xy.first;
    DoubleList y = xy.second;
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
            for (int k = 0; k < f.count(); ++k)
            {
                rectSource = f[k];
                rectGrid = rectByLines(x[i], x[i + 1], y[j], y[j + 1]);
                if (rectSource.contains(rectGrid))
                {
                    res.append(rectGrid);
                    square[i][j] = true;
                    break;
                }
            }
        }
    }
    return Quantum(res, square);
}

Figure maxFigure(Field q)
{
    Figure res;
    ListXY xy = q.first;
    bool **grid = q.second;
    DoubleList x = xy.first;
    DoubleList y = xy.second;

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
