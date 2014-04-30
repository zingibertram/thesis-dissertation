#ifndef MAINPACK_H
#define MAINPACK_H

#include "utils.h"
#include "packing.h"

#include <QGraphicsScene>
#include <QTableWidget>

class Packing
{
public:
    Packing();
    void readFile(QString filename);
    void mainPacking(PackType t);
    void displaySource(QGraphicsScene *gs, int fragIdx);
    void displayResult(QTableWidget *ratio, QTableWidget *coord, QGraphicsScene *gs);
    void saveResult(QString filename);
    void newSource(QString filename);
    void generateSource(QString filename, int cnt = 30);

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
    void displayRatioResult(QTableWidget *ratio);
    void displayCoordsResult(QTableWidget *coords);
    void sourceIdxAccord();
    void saveGeneratedSource(QString filename, FigureList gen);

    FigureList source;
    FigureList input;
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
    IntList sourceReshuffle;
};

#endif // MAINPACK_H
