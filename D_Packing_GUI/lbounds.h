#ifndef LBOUNDS_H
#define LBOUNDS_H

#include "utils.h"

#include <QList>

class LowBounds
{
public:
    LowBounds(FigureVariantList d, QList<bool> iswarg, QList<bool> isharg);
    DoubleList dff_1();
    DoubleList dff_2();
    DoubleList dff_3();
    DoubleList dff_4();

private:
    FigureVariantList data;
    QList<bool> isw;
    QList<bool> ish;
};

#endif // LBOUNDS_H
