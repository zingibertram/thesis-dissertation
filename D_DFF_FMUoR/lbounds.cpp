#include "lbounds.h"

#include <QPoint>

#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

const int eps = 0.000001;

double dff_1_func(double x, int k)
{
    double res = 0;
    double u = x * (k + 1);
    if (fabs((int)u - u) < eps)
    {
        res = x;
    }
    else
    {
        res = (int)u / (double)k;
    }
    //cout << "X = " << x << ", EPS = " << k << ", u^k(x) = " << res << "\n";
    return res;
}

ListDouble dff_1(PackingProblemData data)
{
    ListDouble cnt;
    Figure f;
    double byk;
    double w, h, s;
    //cout << "\n\nDFF 1 >>>>>>>>>>>>>>\n";
    for (int i = 0; i < data.count(); ++i)
    {
        byk = 0;
        f = data[i];
        for (int k = 1; k < 100; ++k)
        {
            //cout << "\n";
            s = 0;
            for (int j = 0; j < f.count(); ++j)
            {
                w = dff_1_func(f[j].width(), k);
                h = dff_1_func(f[j].height(), k);
                s += w * h;
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------

double dff_2_func(double x, double e)
{
    // 0 <= e <= 0.5
    double res = 0;
    if (x > 1.0 - e)
    {
        res = 1;
    }
    else
    {
        if (e <= x)
        {
            res = x;
        }
        else
        {
            res = 0;
        }
    }
    //cout << "X = " << x << ", EPS = " << e << ", U^e(x) = " << res << "\n";
    return res;
}

ListDouble dff_2(PackingProblemData data)
{
    ListDouble cnt;
    Figure f;
    double byk;
    double w, h, s;
    //cout << "\n\nDFF 2 >>>>>>>>>>>>>>\n";
    for (int i = 0; i < data.count(); ++i)
    {
        //cout << "\n";
        byk = 0;
        f = data[i];
        for (double k = 0.0; k <= 0.5; k += 0.0001)
        {
            s = 0;
            for (int j = 0; j < f.count(); ++j)
            {
                w = dff_2_func(f[j].width(), k);
                h = dff_2_func(f[j].height(), k);
                s += w * h;
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------

double dff_3_func(double x, double e)
{

    // 0 <= e < 0.5
    double res = 0;
    if (x > 0.5)
    {
        res = 1.0 - ((int)((1.0 - x) / e)) / ((double)((int)(1.0 / e)));
    }
    else
    {
        if (e <= x)
        {
            res = 1.0 / (double)((int)(1.0 / e));
        }
        else
        {
            res = 0;
        }
    }
    //cout << "X = " << x << ", EPS = " << e << ", F^e(x) = " << res << "\n";
    return res;
}

ListDouble dff_3(PackingProblemData data)
{
    ListDouble cnt;
    Figure f;
    double byk;
    double w, h, s;
    //cout << "\n\nDFF 3 >>>>>>>>>>>>>>\n";
    for (int i = 0; i < data.count(); ++i)
    {
        //cout << "\n";
        byk = 0;
        f = data[i];
        for (double k = 0.0; k < 0.5; k += 0.0001)
        {
            s = 0;
            for (int j = 0; j < f.count(); ++j)
            {
                w = dff_3_func(f[j].width(), k);
                h = dff_3_func(f[j].height(), k);
                s += w * h;
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------
ListDouble dff_4(PackingProblemData data)
{
    ListDouble cnt;
    Figure f;
    double s;
    for (int i = 0; i < data.count(); ++i)
    {
        f = data[i];
        s = 0;
        for (int j = 0; j < f.count(); ++j)
        {
            s += f[j].width() * f[j].height();
        }
        cnt.append(s);
    }
    return cnt;
}

//----------------<Figure fragmentation>----------------

PackingProblemData figureFragmentation(Figure figure)
{
    PackingProblemData res;
    Figure frag;
    Figure resFragmentation;
    Figure maxFragmentation;
    Quantum q;

    for (int i = 0; i < figure.count(); ++i)
    {
        if (figure[i] == sep)
        {
            ListXY xy = gridNodes(frag);
            q = quantumFragmentation(xy, frag);

            //----<Figures output>----
            ListDouble x = xy.first;
            ListDouble y = xy.second;
            bool **grid = q.second;
            for (int j = 0; j < y.count() - 1; ++j)
            {
                for (int i = 0; i < x.count() - 1; ++i)
                {
                    if (grid[i][j])
                    {
                        cout << "+";
                    }
                    else
                    {
                        cout << " ";
                    }
                }
                cout << "\n";
            }
            cout << "\n---------------\n";
            //----<END output>----

            resFragmentation.append(q.first);
            maxFragmentation.append(maxFigure(Field(xy, q.second)));
            frag.clear();
        }
        else
        {
            frag.append(figure[i]);
        }
    }
    res.append(figure);
    res.append(resFragmentation);
    res.append(maxFragmentation);
    cout << "Quantum fragmentation count " << resFragmentation.count() << "\n";
    return res;
}

void insertSorting(ListDouble *l, double d)
{
    double li;
    for (int i = 0; i < l->count(); i++)
    {
        li = l->operator [](i);
        if (fabs(li - d) <= eps)
        {
            return;
        }

        if (li > d + eps)
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
    ListDouble x;
    ListDouble y;
    double xl, xr;
    double yt, yb;
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
//    cout << "\n";
//    for (int i = 0; i < x.count(); ++i)
//    {
//        cout << x[i] << " ";
//    }
//    cout << "\n";
//    for (int i = 0; i < y.count(); ++i)
//    {
//        cout << y[i] << " ";
//    }
//    cout << "\n";
    return ListXY(x, y);
}

RectByLines fromQRect(QRectF r)
{
    RectByLines res;
    res.left = r.x();
    res.right = res.left + r.width();
    res.top = r.y();
    res.bottom = res.top + r.height();
    return res;
}

bool isInclude(RectByLines big, RectByLines small)
{
    bool l = small.left - big.left >= eps;
    bool t = small.top - big.top >= eps;
    bool r = big.right - small.right >= eps;
    bool b = big.bottom - small.bottom >= eps;
    return l && t && r && b;
}

QRectF fromLines(RectByLines r)
{
    double w = r.right - r.left;
    double h = r.bottom - r.top;
    return QRectF(r.left, r.top, w, h);
}

Quantum quantumFragmentation(ListXY xy, Figure f)
{
    ListDouble x = xy.first;
    ListDouble y = xy.second;
    double w, h;
    Figure res;
    RectByLines rectSource, rectGrid;
    bool **square = new bool* [x.count() - 1];
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
                rectSource = fromQRect(f[k]);
                rectGrid = RectByLines(x[i], x[i + 1], y[j], y[j + 1]);
                if (isInclude(rectSource, rectGrid))
                {
                    res.append(fromLines(rectGrid));
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
    ListDouble x = xy.first;
    ListDouble y = xy.second;

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

    QPoint lt, rb;
    bool isAdding;
    int **gridSep = new int* [xSqrCnt];
    for (int i = 0; i < xSqrCnt; ++i)
    {
        gridSep[i] = new int [ySqrCnt];
        memset(gridSep[i], 0, sizeof(int) * ySqrCnt);
    }

    int iter = 1;
    Squares inFigure;

    // сортировка по площади
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
            inFigure.append(VertexPairs(QPoint(l, t), QPoint(r, b)));
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

//    //----<Figures output>----
//    for (int j = 0; j < ySqrCnt; ++j)
//    {
//        for (int i = 0; i < xSqrCnt; ++i)
//        {
//            if (gridSep[i][j])
//            {
//                cout << setw(2) << gridSep[i][j];
//            }
//            else
//            {
//                cout << "--";
//            }
//        }
//        cout << "\n";
//    }
//    cout << "\n---------------\n";
//    //----<END output>----

    for (int i = 0; i < x.count() - 1; ++i)
    {
        delete grid[i];
    }
    delete grid;
    return res;
}
