#ifndef MAINPACK_H
#define MAINPACK_H

#include "utils.h"
#include "packing.h"

#include <QGraphicsScene>
#include <QTableWidget>
#include <QTableWidgetItem>

class Packing
{
public:
    Packing();
    void readFile(QString filename);
    void mainPacking(PackType t);
    void displaySource(QGraphicsScene *gs, int fragIdx);
    void displayResult(QTableWidget *tw, QGraphicsScene *gs);
    void saveSource();
    void newSource(QString filename);

private:
    void figureFragmentation();
    void gridNodes(Figure f);
    Figure quantumFragmentation(DoubleList x, DoubleList y, Figure f);
    Figure maxFigure(DoubleList x, DoubleList y, BoolGrid grid);
    void figuresRect();
    void packing(PackType t);
    void lowBounds();
    void prepareSource();
    void clear();

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
    FigurePacking pack;
};

#endif // MAINPACK_H
