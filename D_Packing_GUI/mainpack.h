#ifndef MAINPACK_H
#define MAINPACK_H

#include "utils.h"

#include <QGraphicsScene>
#include <QTableWidget>
#include <QTableWidgetItem>

class Packing
{
public:
    Packing(char *filename = "data.in");
    void readFile(char *filename);
    void mainPacking();
    void displaySource(QGraphicsScene *gs);
    void displayResult(QTableWidget *tw, QGraphicsScene *gs);

private:
    void figureFragmentation();
    void gridNodes(Figure f);
    Figure quantumFragmentation(DoubleList x, DoubleList y, Figure f);
    Figure maxFigure(DoubleList x, DoubleList y, BoolGrid grid);
    void figuresRect();
    void packing();
    void lowBounds();

    FigureList source;
    Figure figuresBound;
    FigureVariantList data;
    BoolGridList grids;
    DoubleGrid xGrid;
    DoubleGrid yGrid;
    DoubleList xCoor;
    DoubleList yCoor;
    double stripWidth;
    double stripLength;
    int fCount;
    static const int MULT = 100;
    DoubleList dff1;
    DoubleList dff2;
    DoubleList dff3;
    DoubleList dff4;
    double square;
};

#endif // MAINPACK_H
