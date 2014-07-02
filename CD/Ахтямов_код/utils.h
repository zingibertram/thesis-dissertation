#ifndef UTILS_H
#define UTILS_H

#include <QList>
#include <QPair>
#include <QRectF>
#include <QGraphicsScene>
#include <QColor>

enum PackType
{
    BINARY, SEQUENCE
};

typedef QList<int> IntList; // для удобства, чтобы не писать QList<int>

typedef QList<QRectF> Figure; // ортогональный многоугольник - список составляющих его прямоугольников
typedef QList<Figure> FigureList; // список ОМ
typedef QList<FigureList> FigureVariantList; // варианты разбиения входных ОМ

typedef QList<double> DoubleList; // для удобства, чтобы не писать QList<double>
typedef bool** BoolGrid; // сетка расположения минимальных прямоугольников
typedef QList<BoolGrid> BoolGridList; // сетки для всех ОМ
typedef QList<DoubleList> DoubleGrid; // двумерный массив для удобства

typedef QPair<double, double> TupleCoordLength; // элемент кортежа (coord, width)

typedef QPair<int, int> Position; // не помню для чего

typedef double (*DffFunc)(double, double);

extern const double eps; // погрешность для сравнения не целых чисел
extern const double POS_INF; // длина полосы
extern bool isCanceled; // флаг отмены выполнения вычислений

// двойственные функции
double dff_1_func(double x, double e);
double dff_2_func(double x, double e);
double dff_3_func(double x, double e);

// печать фигуры, было нужно в начале
void printFigureGrid(BoolGrid grid, int xcnt, int ycnt);
void printFigureData(Figure f);
void displayFigure(QGraphicsScene *gs, Figure f, double x, double y, double mult, QPen p, QBrush b);
void deleteGrid(BoolGrid grid, int xcnt); // удаление указателей, нужно при считывании новых данных
QRectF rectByFigure(Figure f); // прямоугольник, описывающий ОМ f
double figureSquareReal(Figure f); // площадь ОМ
double figureSquareRect(Figure f); // площадь описанного вокруг ОМ прямоугольника
void sortSource(FigureList *source, bool (*lessFunc)(Figure, Figure)); // упорядочивание ОМ
void rotateFigure(Figure *f, double w); // вращение ОМ

//double rectSquare(QRectF r);
QRectF expand(QRectF r, double m); // увеличение ОМ для удобства печати
bool aContainB(QRectF a, QRectF b); // пересечение прямоугольников

// функции сравнения для величин разных типов, учитывающие погрешность
int epsCompare(double a, double b);
int tupleCompare(const TupleCoordLength &a, const TupleCoordLength &b);
bool tupleLess(const TupleCoordLength &a, const TupleCoordLength &b);
bool positionLess(Position a, Position b);
bool figureLessBySquare(Figure a, Figure b);
bool figureLessByDensity(Figure a, Figure b);
bool figureLessByWidth(Figure a, Figure b);
bool figureLessByHeight(Figure a, Figure b);

void insertSorting(DoubleList *l, double d); // вставка элемента в отсортированный список

bool generateUnequal(DoubleList *ls); // уникальное случайное число
QColor randColor(); // случайный цвет, для печати полосы
double drand(int accuracy); // случайное число

BoolGrid copyGrid(BoolGrid grid, int xcnt, int ycnt); // копирование указателей

#endif // UTILS_H
