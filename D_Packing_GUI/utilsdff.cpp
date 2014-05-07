#include "utils.h"

#include <math.h>

double dff_1_func(double x, double e)
{
    int k = e;
    double res = 0;
    double u = x * (k + 1);
    if (fabs((int)u - u) < eps)
    {
        res = x;
    }
    else
    {
        res = (int)u / (double)k;
    }
    return res;
}

double dff_2_func(double x, double e)
{
    // 0 <= e <= 0.5
    double res = 0;
    if (x > 1.0 - e)
    {
        res = 1;
    }
    else
    {
        if (e <= x)
        {
            res = x;
        }
        else
        {
            res = 0;
        }
    }
    return res;
}

double dff_3_func(double x, double e)
{

    // 0 <= e < 0.5
    double res = 0;
    if (x > 0.5)
    {
        res = 1.0 - ((int)((1.0 - x) / e)) / ((double)((int)(1.0 / e)));
    }
    else
    {
        if (e <= x)
        {
            res = 1.0 / (double)((int)(1.0 / e));
        }
        else
        {
            res = 0;
        }
    }
    return res;
}
