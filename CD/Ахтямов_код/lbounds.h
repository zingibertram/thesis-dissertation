#ifndef LBOUNDS_H
#define LBOUNDS_H

#include "utils.h"
#include "knapsacksolver.h"

#include <QList>

class LowBounds // вычисление нижних границ
{
public:
    LowBounds(DoubleGrid w, DoubleGrid h, IntList cnt); // w[i] (h[i]) - ширинs (высоты) всех прямоугольников всех ОМ
                                                        // cnt - количество прямоугольников в соответствующем варианте
    // вычисление двойственных функций
    DoubleList dff_1();
    DoubleList dff_2();
    DoubleList dff_3();
    double dffMaximum(bool isMaximize); // максимизированная оценка

private:
    double maximizeDff(); // максимизация DFF

    DoubleList dff(double minParam, double maxParam, double plusParam, DffFunc func);

    double dffMax;
    double subMax;

    // максимальные значения двойственной функции и соответствующие им размеры
    int owls;
    int ohls;
    DoubleList hls;

    DoubleGrid widthByDataVariant;
    DoubleGrid heightByDataVariant;
    int variantCount;
    IntList countByVariant;
};

#endif // LBOUNDS_H
