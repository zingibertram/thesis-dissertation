#include "utils.h"

#include <stdio.h>
#include <math.h>
#include <iostream>

#include <QtGui/QApplication>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

using namespace std;

const double eps = 0.0001;

FigureList readFile(char *filename)
{
    freopen(filename, "r", stdin);
    int num;
    cin >> num;
    double k, x, y, w, h;
    Figure f;
    FigureList res;
    for (int i = 0; i < num; ++i)
    {
        f.clear();
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            cin >> x >> y >> w >> h;
            f.append(QRectF(x, y, w, h));
        }
        res.append(f);
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

QRectF expand(QRectF r, double m)
{
    double x = r.x();
    double y = r.y();
    double w = r.width();
    double h = r.height();
    return QRectF(x * m, y * m, w * m, h * m);
}

int showRect(Figure f, QRectF back)
{
    char *c = "sdf";
    char **args = new char*;
    args[0] = c;
    int a = 1;
    QApplication app(a, &c);

    QGraphicsScene gs(0, 0, 500, 500);
    QGraphicsView gv;
    gv.setScene(&gs);

    gs.addRect(expand(back, 100), QPen(Qt::black), QBrush(Qt::green));

    for (int i = 0; i < f.count(); ++i)
    {
        QRectF r = expand(f[i], 100);
        gs.addRect(r, QPen(Qt::black), QBrush(Qt::red));
    }

    gv.show();

    return app.exec();
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

void printCortage(Cortage c)
{
    cout << endl << "CORTAGE: ";
    for (int i = 0; i < c.count(); ++i)
    {
        cout << "(" << c[i].first << ", " << c[i].second << "), ";
    }
    cout << endl;
}

void printDoubleList(DoubleList dl)
{
    cout << endl << "DOUBLE LIST: ";
    for (int i = 0; i < dl.count(); ++i)
    {
        cout << dl[i] << ", ";
    }
    cout << endl;
}
