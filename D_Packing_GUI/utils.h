#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QPair>
#include <QRectF>
#include <QGraphicsScene>
#include <QColor>

typedef QList<QRectF> Figure;
typedef QList<Figure> FigureList;
typedef QList<FigureList> FigureVariantList;

typedef QList<double> DoubleList;
typedef bool** BoolGrid;
typedef QList<BoolGrid> BoolGridList;
typedef QList<DoubleList> DoubleGrid;

typedef QPair<double, double> TupleCoordLength; // (coord, width)

extern const double eps;

double dff_1_func(double x, int k);
double dff_2_func(double x, double e);
double dff_3_func(double x, double e);

void printFigureGrid(BoolGrid grid, int xcnt, int ycnt);
void deleteGrid(BoolGrid grid, int xcnt);

double rectSquare(QRectF r);
QRectF rectByLines(double l, double r, double t, double b);
QRectF expand(QRectF r, double m);
QRectF rectByFigure(Figure f);
void displayFigure(QGraphicsScene *gs, Figure f, double x, double y, double mult, QPen p, QBrush b);

int epsCompare(double a, double b);
int tupleCompare(const TupleCoordLength &a, const TupleCoordLength &b);
bool tupleLess(const TupleCoordLength &a, const TupleCoordLength &b);
void insertSorting(DoubleList *l, double d);

QColor randColor();

#endif // UTILS_H
