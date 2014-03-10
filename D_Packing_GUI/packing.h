#ifndef PACKING_H
#define PACKING_H

#include "utils.h"

typedef QList<TupleCoordLength> Cortage;
typedef QList<Cortage> CortageList;

class FigurePacking
{
public:
    FigurePacking();
    FigurePacking(FigureList fs, BoolGridList gs, DoubleGrid x, DoubleGrid y, double w, double l, Figure bound);
    double squarePacking();
    DoubleList xPositions();
    DoubleList yPositions();
    void pack();
    FigureList xCortToFig();
    FigureList yCortToFig();

private:
    void figuresToCortage();
    Cortage figureToCortage(BoolGrid grid, DoubleList coor, DoubleList width, bool xy);
    Cortage sum(Cortage *c1, Cortage *c2);
    Cortage* insertCortage(Cortage *src, Cortage *ins);
    void packCortage();
    bool checkSize(Cortage *x, double w, double l);
    bool checkOverlap(double nx, double ny, int cnt);
    DoubleList getCortageCoords(Cortage src, Cortage ins);
    DoubleList getTightCoords(Cortage src, Cortage ins);
    void shiftCortage(Cortage *c, double shift, double prevShift);
    bool intersect(int n, int f);

    FigureList source;
    BoolGridList grids;
    DoubleGrid xGrid;
    DoubleGrid yGrid;
    double stripWidth;
    double stripLength;
    int count;
    DoubleList xPos;
    DoubleList yPos;
    CortageList xCortage;
    CortageList yCortage;
    double square;
    Figure figuresBound;
};

#endif // PACKING_H
