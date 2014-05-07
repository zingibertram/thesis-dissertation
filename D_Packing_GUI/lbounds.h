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
    double dffMaximum(); // максимизированная оценка

private:
    double maximizeDff(); // максимизация DFF

    DoubleList dff(double minParam, double maxParam, double plusParam, DffFunc func);

    FigureVariantList data;
    QList<bool> isw;
    QList<bool> ish;

    double dffMax;

    // максимальные значения двойственной функции и соответствующие им размеры
    DoubleList owls;
    DoubleList wls;
    DoubleList ohls;
    DoubleList hls;

    DoubleGrid widthByDataVariant;
    DoubleGrid heightByDataVariant;
    int variantCount;
    IntList countByVariant;
};

#endif // LBOUNDS_H
