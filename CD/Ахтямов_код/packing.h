#ifndef PACKING_H
#define PACKING_H

#include "utils.h"

typedef QList<TupleCoordLength> Cortage;
typedef QList<Cortage> CortageList;

class FigurePacking // упаковщик
{
public:
    FigurePacking(); // конструктор
    FigurePacking(FigureList fs, BoolGridList gs, DoubleGrid x, DoubleGrid y, double w, double l, Figure bound); // конструктор
    double squarePacking(); // площадь упаковки
    DoubleList xPositions(); // х-координаты размещённых ОМ
    DoubleList yPositions(); // у-координаты размещённых ОМ
    void pack(); // упаковка и оценка
    // представление кортежей как ОМ, нужно для подсчёта оценок
    FigureList xCortToFig();
    FigureList yCortToFig();

public:
    void packBinaryTree(); // упаковка двоичным деревом
private:
    void packCortageBinaryTree(); // упаковка двоичным деревом
    void packTreeLeafPair(int l, int r); // упаковка 2-х листьев дерева
    void sumFigure(int l, int r, double x, double y, Cortage cx, Cortage cy); // 2 упакованные фигуры превращаются в 1
    bool checkOverlapPair(int l, int r, double nx, double ny); // проверка пересечения двух ОМ
    QList<QList<int> > rectLeafs; // индексы ОМ в source, которые сложились в 1
    FigureList sourceBin; // копия source

private:
    void figuresToCortage(); // превращение фигур в кортежи
    Cortage figureToCortage(BoolGrid grid, DoubleList coor, DoubleList width, bool xy); // превращение фигуры в кортеж
    Cortage sum(Cortage *c1, Cortage *c2); // сумма двух кортежей
    Cortage* insertCortage(Cortage *src, Cortage *ins); // вставка кортежа ins в src, нужно для сложения
    void packCortage(); // упаковка
    bool checkSize(Cortage *x, double w, double l); // проверка необходимого условия (проверка размеров)
    bool checkOverlap(double nx, double ny, int cnt); // проверка достаточного условия (непересечение)
    DoubleList getCortageCoords(Cortage src, Cortage ins); // упорядоченные координаты из двух кортежей
    DoubleList getTightCoords(Cortage src, Cortage ins); // упорядоченные координаты из двух кортежей
    void shiftCortage(Cortage *c, double shift, double prevShift); // свиг кортежа
//    bool intersect(int n, int f);

    // для получения кортежей
    BoolGridList grids; // сетка
    DoubleGrid xGrid; // координаты узлов по вертикали
    DoubleGrid yGrid; // координаты узлов по горизонтали

    // следующие поля обозначают именно то, какое у них название
    FigureList source; // исходные ОМ
    double stripWidth;
    double stripLength;
    int count;
    DoubleList xPos;
    DoubleList yPos;
    CortageList xCortage;
    CortageList yCortage;
    double square;
    Figure figuresBound;
};

#endif // PACKING_H
