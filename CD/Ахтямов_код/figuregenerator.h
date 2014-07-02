#ifndef FIGUREGENERATOR_H
#define FIGUREGENERATOR_H

#include "utils.h"

class FigureGenerator // генератор входных данных
{
public:
    FigureGenerator(); // конструктор
    static DoubleList generateDoubles(int cnt); // генерация сетки (отдельно вертикальные и горизонтальные узлы)
    static bool checkConnection(BoolGrid grid, int i, int j, int cx, int cy); // проверка сетки на связность
    static Figure gridToFigure(BoolGrid grid, DoubleList x, DoubleList y, int ce); // заполнение некоторых ячеек сетки
    static Figure generateFigure(int cx = 5, int cy = 4); // генерация фигуры с заданным размером сетки
    static FigureList generateSource(int cnt = 30); // генерация списка ОМ заданного количества
};

#endif // FIGUREGENERATOR_H
