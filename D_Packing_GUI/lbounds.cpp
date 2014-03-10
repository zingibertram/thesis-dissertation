#include "lbounds.h"

#include <math.h>

using namespace std;

LowBounds::LowBounds(FigureVariantList d)
{
    data = d;
}

DoubleList LowBounds::dff_1()
{
    DoubleList cnt;
    double byk;
    double w, h, s;
    for (int i = 0; i < data.count(); ++i)
    {
        byk = 0;
        for (int k = 1; k < 100000; ++k)
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

DoubleList LowBounds::dff_2()
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

DoubleList LowBounds::dff_3()
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

DoubleList LowBounds::dff_4()
{
    DoubleList cnt;
    double s;
    for (int i = 0; i < data.count(); ++i)
    {
        s = 0;
        for (int l = 0; l < data[i].count(); ++l)
        {
            s += figureSquareReal(data[i][l]);
        }
        cnt.append(s);
    }
    return cnt;
}
