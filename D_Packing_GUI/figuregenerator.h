#ifndef FIGUREGENERATOR_H
#define FIGUREGENERATOR_H

#include "utils.h"

class FigureGenerator
{
public:
    FigureGenerator();
    static DoubleList generateDoubles(int cnt);
    static bool checkConnection(BoolGrid grid, int i, int j, int cx, int cy);
    static Figure gridToFigure(BoolGrid grid, DoubleList x, DoubleList y, int ce);
    static Figure generateFigure(int cx = 5, int cy = 4);
    static FigureList generateSource(int cnt = 30);
};

#endif // FIGUREGENERATOR_H
