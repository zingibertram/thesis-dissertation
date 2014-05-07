#ifndef KNAPSACKSOLVER_H
#define KNAPSACKSOLVER_H

#include "utils.h"

class KnapsackSolver // решение задачи о рюкзаке, нужно для максимизации двойственных функций
{
public:
    KnapsackSolver();
    KnapsackSolver(DoubleList w, DoubleList p, double c);
    double solve(int idx); // решение методом динамического программирования с использованием удельной цены объектов

private:
    void sortByRatio(); // упорядочивание по удельной цене
    bool stepDown(); // удалить вещь из рюкзака
    double maxRatio(); // текущая максимальная удельная цена

    DoubleList weight;
    DoubleList coast;
    double capacity;
    double allCapacity;
    int count;

    DoubleList ratio;
    IntList isPack;
    IntList idxAccord;
    double currentWeight;
    double currentCoast;
    double maxCost;
    bool flag;
    int prevMaxIdx;
    int index;

    int withoutIdx;
};

#endif // KNAPSACKSOLVER_H
