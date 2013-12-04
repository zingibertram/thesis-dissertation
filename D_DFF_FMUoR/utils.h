#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QRectF>

typedef QList<QRectF> Figure;
typedef QList<Figure> PackingProblemData;
typedef QList<Figure> FigureList;

extern const QRectF sep;

Figure readFile(char *filename);
void printFigures(FigureList f);

#endif // UTILS_H
