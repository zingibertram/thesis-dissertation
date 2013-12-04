#include "lbounds.h"

#include <math.h>

using namespace std;

double dff_1_func(double x, int k)
{
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

DoubleList dff_1(FigureVariantList data)
{
    DoubleList cnt;
    double byk;
    double w, h, s;
    for (int i = 0; i < data.count(); ++i)
    {
        byk = 0;
        for (int k = 1; k < 100; ++k)
        {
            s = 0;
            for (int l = 0; l < data[i].count(); ++l)
            {
                for (int j = 0; j < data[i][l].count(); ++j)
                {
                    w = dff_1_func(data[i][l][j].width(), k);
                    h = dff_1_func(data[i][l][j].height(), k);
                    s += w * h;
                }
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------

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

DoubleList dff_2(FigureVariantList data)
{
    DoubleList cnt;
    double byk;
    double w, h, s;
    for (int i = 0; i < data.count(); ++i)
    {
        byk = 0;
        for (double k = 0.0; k <= 0.5; k += 0.0001)
        {
            s = 0;
            for (int l = 0; l < data[i].count(); ++l)
            {
                for (int j = 0; j < data[i][l].count(); ++j)
                {
                    w = dff_2_func(data[i][l][j].width(), k);
                    h = dff_2_func(data[i][l][j].height(), k);
                    s += w * h;
                }
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------

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

DoubleList dff_3(FigureVariantList data)
{
    DoubleList cnt;
    double byk;
    double w, h, s;
    for (int i = 0; i < data.count(); ++i)
    {
        byk = 0;
        for (double k = 0.0; k < 0.5; k += 0.0001)
        {
            s = 0;
            for (int l = 0; l < data[i].count(); ++l)
            {
                for (int j = 0; j < data[i][l].count(); ++j)
                {
                    w = dff_3_func(data[i][l][j].width(), k);
                    h = dff_3_func(data[i][l][j].height(), k);
                    s += w * h;
                }
            }
            if (s > byk)
            {
                byk = s;
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

//-------------<>----------------
DoubleList dff_4(FigureVariantList data)
{
    DoubleList cnt;
    double s;
    for (int i = 0; i < data.count(); ++i)
    {
        s = 0;
        for (int l = 0; l < data[i].count(); ++l)
        {
            for (int j = 0; j < data[i][l].count(); ++j)
            {
                s += data[i][l][j].width() * data[i][l][j].height();
            }
        }
        cnt.append(s);
    }
    return cnt;
}

//----------------<Figure fragmentation>----------------
