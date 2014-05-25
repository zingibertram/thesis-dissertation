#include "knapsacksolver.h"

KnapsackSolver::KnapsackSolver()
{
    count = 0;
}

KnapsackSolver::KnapsackSolver(DoubleList w, DoubleList p, double c)
{
    weight = w;
    coast = p;
    allCapacity = c;
    count = std::min(w.count(), p.count());

    idxAccord.clear();
    ratio.clear();

    for (int i = 0; i < count; ++i)
    {
        ratio << coast[i] / weight[i];
        idxAccord << i;
    }
    this->sortByRatio();
}

double KnapsackSolver::solve(int idx)
{
    withoutIdx = idxAccord.indexOf(idx);
    capacity = allCapacity - weight[withoutIdx];
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
        if ((capacity - currentWeight) * this->maxRatio() + currentCoast <= maxCost)
        {
            flag = false;
        }
        else
        {
            for(int  i = index; i < count; ++i)
            {
                if (i == withoutIdx)
                {
                    continue;
                }

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

        if (allCapacity - maxCost <= coast[withoutIdx])
        {
            break;
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
                idxAccord.swap(i, j);
            }
        }
    }
}

bool KnapsackSolver::stepDown()
{
    for(int i = count - 1; i >= 0; --i)
    {
        if (i == withoutIdx)
        {
            continue;
        }

        if(isPack[i])
        {
            currentWeight -= weight[i];
            currentCoast -= coast[i];
            isPack[i] = 0;
//            if (i != count - 1)
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
    int i = index;
    for (; i < count; ++i)
    {
        if (i == withoutIdx)
        {
            continue;
        }

        if (!isPack[i])
        {
            return ratio[i];
        }
    }

//    for (; i < count; ++i)
//    {
//        if (i == withoutIdx)
//        {
//            continue;
//        }

//        if (!isPack[i])
//        {
//            return ratio[i];
//        }
//    }
    return 0;
}
