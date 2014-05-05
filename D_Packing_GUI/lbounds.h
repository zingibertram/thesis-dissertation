#ifndef LBOUNDS_H
#define LBOUNDS_H

#include "utils.h"
#include "knapsacksolver.h"

#include <QList>

class LowBounds // вычисление нижних границ
{
public:
    LowBounds(FigureVariantList d, QList<bool> iswarg, QList<bool> isharg); // d - варианты разбиений ОМ
                                                                            // iswarg, isharg - применять или нет двойственную функцию к ширине/высоте
    // вычисление двойственных функций
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
