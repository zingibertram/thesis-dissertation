#ifndef PACKING_H
#define PACKING_H

#include "utils.h"

typedef QList<TupleCoordLength> Cortage;
typedef QList<Cortage> CortageList;

class FigurePacking
{
public:
    FigurePacking(FigureList fs, BoolGridList gs, DoubleGrid x, DoubleGrid y, double w, double l);
    double squarePacking();
    DoubleList xPositions();
    DoubleList yPositions();
    void pack();

private:
    void figuresToCortage();
//    void figureCortage(BoolGrid grid, DoubleList x, DoubleList y);
    Cortage figureToCortage(BoolGrid grid, DoubleList coor, DoubleList width, bool xy);
    Cortage sum(Cortage c1, Cortage c2);
    Cortage insertCortage(Cortage src, Cortage ins);
    void packCortage();
    bool checkSize(Cortage x, double w, double l);
    bool checkOverlap(double nx, double ny, int cnt);
    DoubleList getCortageCoords(Cortage src, Cortage ins);
    DoubleList getTightCoords(Cortage src, Cortage ins);
    void shiftCortage(Cortage *c, double shift, double prevShift);

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
};

#endif // PACKING_H
