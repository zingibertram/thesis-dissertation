#include "utils.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

using namespace std;

const double eps = 0.0001;

// Двойственные функции

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
    return res;
}

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
    return res;
}

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
    return res;
}



void printFigureGrid(BoolGrid grid, int xcnt, int ycnt)
{
    for (int i = 0; i < ycnt; ++i)
    {
        for (int j = 0; j < xcnt; ++j)
        {
            if (grid[j][i])
            {
                cout << "X";
            }
            else
            {
                cout << "-";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

void deleteGrid(BoolGrid grid, int xcnt)
{
    for (int i = 0; i < xcnt; ++i)
    {
        delete grid[i];
    }
    delete grid;
}

double rectSquare(QRectF r)
{
    return r.width() * r.height();
}

QRectF rectByLines(double l, double r, double t, double b)
{
    return QRectF(l, t, r - l, b - t);
}

QRectF expand(QRectF r, double m)
{
    double x = r.x();
    double y = r.y();
    double w = r.width();
    double h = r.height();
    return QRectF(x * m, y * m, w * m, h * m);
}

void showPacking(QGraphicsScene *gs, FigureList fs, DoubleList x, DoubleList y)
{
    ;
}

int epsCompare(double a, double b)
{
    if (fabs(a - b) <= eps)
    {
        return 0;
    }
    if (a - b > eps)
    {
        return 1;
    }
    return -1;
}

int tupleCompare(const TupleCoordLength &a, const TupleCoordLength &b)
{
    double af = a.first;
    double bf = b.first;
    return epsCompare(af, bf);
}

bool tupleLess(const TupleCoordLength &a, const TupleCoordLength &b)
{
    return tupleCompare(a, b) == -1;
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

QRectF rectByFigure(Figure f)
{
    double width = 0.0;
    double height = 0.0;
    double w, h;
    for (int i = 0; i < f.count(); ++i)
    {
        w = f[i].x() + f[i].width();
        h = f[i].y() + f[i].height();
        if (w > width)
        {
            width = w;
        }
        if (h > height)
        {
            height = h;
        }
    }
    return QRectF(0.0, 0.0, width, height);
}

void displayFigure(QGraphicsScene *gs, Figure f, double x, double y, double mult, QPen p, QBrush b)
{
    QRectF expanded;
    for (int i = 0; i < f.count(); ++i)
    {
        expanded = expand(f[i], mult);
        expanded.moveTo(x * mult + expanded.x(), y * mult + expanded.y());
        gs->addRect(expanded, p, b);
    }
}

QColor randColor()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return QColor(r, g, b);
}
