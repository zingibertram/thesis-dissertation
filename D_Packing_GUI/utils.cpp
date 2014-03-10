#include "utils.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <qmath.h>
#include <qalgorithms.h>

using namespace std;

const double eps = 0.0001;

const double POS_INF = 1.0E36;

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
    char *str = new char[xcnt + 1];
    str[xcnt] = 0;
    for (int i = 0; i < ycnt; ++i)
    {
        for (int j = 0; j < xcnt; ++j)
        {
            if (grid[j][i])
            {
                str[j] = 'X';
            }
            else
            {
                str[j] = '-';
            }
        }
        qDebug() << str;
    }
    qDebug() << "\n";
}

void printFigureData(Figure f)
{

    QRectF r;
    qDebug() << f.count();
    for (int i = 0; i < f.count(); ++i)
    {
        r = f[i];
        qDebug() << r.x() << " " << r.y()  << " " << r.width()  << " " << r.height();
    }
}

void deleteGrid(BoolGrid grid, int xcnt)
{
    for (int i = 0; i < xcnt; ++i)
    {
        delete grid[i];
    }
    delete grid;
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

bool generateUnequal(DoubleList *ls)
{
    double d, old, p;
    old = ls->operator [](ls->count() - 1);
    p = drand(5);
    d = old + p;
    if (d < 1.0 + eps)
    {
        ls->append(d);
        return true;
    }
    return false;
}

double drand(int accuracy)
{
    double p = qPow(10, accuracy);
    double a = (qrand() % ((int)p + 1)) / p;
    double b = (qrand() % 1000) / 2500.0 + 0.002;
    return b;
}

bool positionLess(Position a, Position b)
{
    int ai = a.first;
    int bi = b.first;
    int aj = a.second;
    int bj = b.second;
    if (ai < bi || (ai == bi && aj < bj))
    {
        return true;
    }
    return false;
}

bool aContainB(QRectF a, QRectF b)
{
    bool pos = (a.x() <= b.x() + eps) && (a.y() <= b.y() + eps);
    bool right = (a.x() + a.width() + eps >= b.x() + b.width());
    bool bottom = (a.y() + a.height() + eps >= b.y() + b.height());
    bool res = pos && right && bottom;
    return res;
}

double figureSquareReal(Figure f)
{
    double s = 0;
    for (int i = 0; i < f.count(); ++i)
    {
        s += f[i].width() * f[i].height();
    }
    return s;
}

double figureSquareRect(Figure f)
{
    QRectF r = rectByFigure(f);
    return r.width() * r.height();
}

bool figureLessBySquare(Figure a, Figure b)
{
    return figureSquareReal(a) < figureSquareReal(b);
}

bool figureLessByDensity(Figure a, Figure b)
{
    return figureSquareRect(a) / figureSquareReal(a) < figureSquareRect(b) / figureSquareReal(b);
}

bool figureLessByWidth(Figure a, Figure b)
{
    return rectByFigure(a).width() > rectByFigure(b).width();
}

bool figureLessByHeight(Figure a, Figure b)
{
    return rectByFigure(a).height() > rectByFigure(b).height();
}

void sortSource(FigureList *source, bool (*lessFunc)(Figure, Figure))
{
    qSort(source->begin(), source->end(), lessFunc);
}

BoolGrid copyGrid(BoolGrid grid, int xcnt, int ycnt)
{
    BoolGrid res = new bool* [xcnt];
    for (int i = 0; i < xcnt; ++i)
    {
        res[i] = new bool [ycnt];
        for (int j = 0; j < ycnt; ++j)
        {
            res[i][j] = grid[i][j];
        }
    }
    return res;
}

void rotateFigure(Figure *f)
{
    for (int i = 0; i < f->count(); ++i)
    {
        (*f)[i] = QRectF((*f)[i].y(), (*f)[i].x(), (*f)[i].height(), (*f)[i].width());
    }
}
