#ifndef MAINPACK_H
#define MAINPACK_H

#include "utils.h"
#include "packing.h"
#include "translation.h"

#include <QObject>
#include <QGraphicsScene>
#include <QTableWidget>
#include <QMessageBox>

class Packing : public QObject // модель упаковки
{
    Q_OBJECT // макрос для использования специальных функций

public:
    Packing();
    void readFile(QString filename); // считать исходные данные
    void mainPacking(PackType t); // упаковка указанным типом
    void displaySource(QGraphicsScene *gs, int fragIdx); // вывести исходные данные
    void displayResult(QTableWidget *ratio, QTableWidget *coord, QGraphicsScene *gs); // вывести результат
    void saveResult(QString filename); // сохранить результат
    void newSource(QString filename); // загрузить новые исходные данные
    void generateSource(QString filename, int cnt = 30); // генерировать исходные данные
    int sourceCount(); // количество ОМ
    bool isCalculated(); // проверка, произведены ли вычисления

private:
    void figureFragmentation(); // фрагментация ОМ - разбиение на минимальные прямоугольники и заполнение сетки
    void gridNodes(Figure f); // узлы сетки ОМ
    Figure quantumFragmentation(DoubleList x, DoubleList y, Figure f); // минимальное разбиение фигуры
    Figure maxFigure(DoubleList x, DoubleList y, BoolGrid grid); // максимальное разбиение фигуры
    void figuresRect(); // заполнение списка описанных вокруг ОМ прямоугольников
    void packing(PackType t); // упаковка способом t
    void lowBounds(); // вычисление нижних границ
    void prepareSource(); // подготовка исходных данных к вычислению
    void clear(); // очистка модели
    void displayRatioResult(QTableWidget *ratio); // вывод результатов нижних границ
    void displayCoordsResult(QTableWidget *coords); // вывод результатов упаковки
    void sourceIdxAccord(); // соответствие исходного порядка ОМ и после изменения
    void saveGeneratedSource(QString filename, FigureList gen); // сохранение сгенерированных данных

    FigureList source;
    FigureList input;
    Figure figuresBound;
    FigureVariantList data;
    BoolGridList grids;
    DoubleGrid xGrid;
    DoubleGrid yGrid;
    DoubleList xCoor;
    DoubleList yCoor;
    double stripWidth;
    double stripLength;
    double packDensity;
    int fCount;
    static const int MULT = 100;
    DoubleList dff1;
    DoubleList dff2;
    DoubleList dff3;
    double dffMaximum;
    double square;
    FigurePacking pack;
    IntList sourceReshuffle;

signals:
    void packingEnd();
};

#endif // MAINPACK_H
