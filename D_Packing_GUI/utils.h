#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QPair>
#include <QRectF>

typedef QList<QRectF> Figure;
typedef QList<Figure> FigureList;
typedef QList<FigureList> FigureVariantList;

typedef QList<double> DoubleList;
typedef bool** BoolGrid;

typedef QPair<DoubleList, DoubleList> ListXY;
typedef QPair<ListXY, BoolGrid> Field;
typedef QPair<Figure, BoolGrid> Quantum;

typedef QPair<double, double> TupleCoordLength; // (coord, width)
typedef QList<TupleCoordLength> Cortage;
typedef QPair<Cortage, Cortage> CortageXY;
typedef QList<CortageXY> CortageList;
typedef QPair<DoubleList, DoubleList> TupleCoord; // ([x ccoords], [y coords])

extern const double eps;

FigureList readFile(char *filename);
void printFigureGrid(BoolGrid grid, int xcnt, int ycnt);
void deleteGrid(BoolGrid grid, int xcnt);
double rectSquare(QRectF r);

int showRect(Figure f, QRectF back);

int epsCompare(double a, double b);
int tupleCompare(const TupleCoordLength &a, const TupleCoordLength &b);
bool tupleLess(const TupleCoordLength &a, const TupleCoordLength &b);
void printCortage(Cortage c);
void printDoubleList(DoubleList dl);

#endif // UTILS_H
