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

typedef QPair<int, int> Position;

extern const double eps;

double dff_1_func(double x, int k);
double dff_2_func(double x, double e);
double dff_3_func(double x, double e);

void printFigureGrid(BoolGrid grid, int xcnt, int ycnt);
void printFigureData(Figure f);
void deleteGrid(BoolGrid grid, int xcnt);
QRectF rectByFigure(Figure f);
void displayFigure(QGraphicsScene *gs, Figure f, double x, double y, double mult, QPen p, QBrush b);
double figureSquareReal(Figure f);
double figureSquareRect(Figure f);
void sortSource(FigureList *source);

//double rectSquare(QRectF r);
QRectF expand(QRectF r, double m);
bool aContainB(QRectF a, QRectF b);

int epsCompare(double a, double b);
int tupleCompare(const TupleCoordLength &a, const TupleCoordLength &b);
bool tupleLess(const TupleCoordLength &a, const TupleCoordLength &b);
void insertSorting(DoubleList *l, double d);
bool positionLess(Position a, Position b);
bool figureLessBySquare(Figure a, Figure b);
bool figureLessByDensity(Figure a, Figure b);

bool generateUnequal(DoubleList *ls);
QColor randColor();
double drand(int accuracy);

BoolGrid copyGrid(BoolGrid grid, int xcnt, int ycnt);

#endif // UTILS_H
