#ifndef PACKING_H
#define PACKING_H

#include "utils.h"

CortageXY figureCortage(Figure f);
Cortage sum(Cortage c1, Cortage c2);
Cortage insertCortage(Cortage src, Cortage ins);
DoubleList packCortage(CortageList ls);
bool checkSize(Cortage x, Cortage y, double w, double l);
bool checkOverlap(FigureList fs, DoubleList posx, DoubleList posy, double nx, double ny, int cnt);

#endif // PACKING_H
