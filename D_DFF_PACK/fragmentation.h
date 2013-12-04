#ifndef FRAGMENTATION_H
#define FRAGMENTATION_H

#include "utils.h"
#include <iostream>
#include <iomanip>

FigureVariantList figureFragmentation(FigureList data);
void insertSorting(DoubleList *l, double d);
ListXY gridNodes(Figure f);
Quantum quantumFragmentation(ListXY xy, Figure f);
Figure maxFigure(Field q);
QRectF rectByLines(double l, double r, double t, double b);

#endif // FRAGMENTATION_H
