#include "knapsacksolver.h"

KnapsackSolver::KnapsackSolver(DoubleList w, DoubleList p, double c)
{
    weight = w;
    coast = p;
    capacity = c;
    count = std::min(w.count(), p.count());

    for (int i = 0; i < count; ++i)
    {
        ratio << coast[i] / weight[i];
    }
    this->sortByRatio();
}

double KnapsackSolver::solve()
{
    flag = true;
    currentWeight = 0;
    currentCoast = 0;
    maxCost = 0;
    index = 0;
    isPack = IntList();
    for (int i = 0; i < count; ++i)
    {
        isPack << 0;
    }

    do
    {
        // stepup
        if ((capacity - currentWeight) * this->maxRatio() + currentCoast < maxCost)
        {
            flag = false;
        }
        else
        {
            for(int  i = index; i < count; ++i)
            {
                if(currentWeight + weight[i] <= capacity)
                {
                    currentWeight += weight[i];
                    currentCoast += coast[i];
                    isPack[i] = 1;
                }
                else
                {
                    isPack[i] = 0;
                }
            }
            flag = true;
        }

        //mark
        if(!flag || currentCoast < maxCost)
        {
            continue;
        }
        if(currentCoast > maxCost)
        {
            maxCost = currentCoast;
        }
    } while (this->stepDown());


    return maxCost;
}

void KnapsackSolver::sortByRatio()
{
    int j;
    for (int i = 0; i < count; ++i)
    {
        for (j = i + 1; j < count; ++j)
        {
            if (ratio[i] < ratio[j])
            {
                ratio.swap(i, j);
                coast.swap(i, j);
                weight.swap(i, j);
            }
        }
    }
}

bool KnapsackSolver::stepDown()
{
    for(int i = count - 1; i >= 0; --i)
    {
        if(isPack[i])
        {
            currentWeight -= weight[i];
            currentCoast -= coast[i];
            isPack[i] = 0;
            if (i != count - 1)
            {
                index = i + 1;
                return true;
            }
        }
    }
    return false;
}

double KnapsackSolver::maxRatio()
{
    int i = 0;
    for (; i < count; ++i)
    {
        if (isPack[i])
        {
            break;
        }
    }
    for (; i < count; ++i)
    {
        if (!isPack[i])
        {
            return ratio[i];
        }
    }
    return 0;
}