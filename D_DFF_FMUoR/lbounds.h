#ifndef LBOUNDS_H
#define LBOUNDS_H

#include "utils.h"
#include <QList>
#include <QPair>

extern const int eps;

typedef QList<double> ListDouble;
typedef QPair<ListDouble, ListDouble> ListXY;
typedef QPair<ListXY, bool**> Field;
typedef QPair<Figure, bool**> Quantum;

ListDouble dff_1(PackingProblemData data);
ListDouble dff_2(PackingProblemData data);
ListDouble dff_3(PackingProblemData data);
ListDouble dff_4(PackingProblemData data);

PackingProblemData figureFragmentation(Figure data);
void insertSorting(ListDouble *l, double d);
ListXY gridNodes(Figure f);
Quantum quantumFragmentation(ListXY xy, Figure f);
Figure maxFigure(Field q);

struct RectByLines
{
    RectByLines() {}
    RectByLines(double l, double r, double t, double b) {top = t; bottom = b; left = l; right = r;}
    double top;
    double bottom;
    double left;
    double right;
};

RectByLines fromQRect(QRectF r);
bool isInclude(RectByLines big, RectByLines small);
QRectF fromLines(RectByLines r);

#endif // LBOUNDS_H
