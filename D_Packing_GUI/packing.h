#ifndef PACKING_H
#define PACKING_H

#include "utils.h"

CortageXY figureCortage(Figure f);
Cortage sum(Cortage c1, Cortage c2);
Cortage insertCortage(Cortage src, Cortage ins);
CortageList figuresToCortage(FigureList fs);
TupleCoord packCortage(CortageList ls, FigureList fs);
bool checkSize(Cortage x, double w, double l);
bool checkOverlap(FigureList fs, DoubleList posx, DoubleList posy, double nx, double ny, int cnt);
double squarePacking(TupleCoord tc, FigureList fs);
DoubleList getCortageCoords(Cortage cort);
Cortage shiftCortage(Cortage c, double shift);

#endif // PACKING_H
