#ifndef LBOUNDS_H
#define LBOUNDS_H

#include "utils.h"

class LowBounds
{
public:
    LowBounds(FigureVariantList d);
    DoubleList dff_1();
    DoubleList dff_2();
    DoubleList dff_3();
    DoubleList dff_4();

private:
    FigureVariantList data;
};

#endif // LBOUNDS_H
