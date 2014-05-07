#include "lbounds.h"

#include <math.h>

using namespace std;

LowBounds::LowBounds(FigureVariantList d, QList<bool> iswarg, QList<bool> isharg)
{
    data = d;
    isw = iswarg;
    ish = isharg;
    dffMax = 0;

    variantCount = d.count();
    countByVariant.clear();
    widthByDataVariant.clear();
    heightByDataVariant.clear();
    for (int i = 0; i < d.count(); ++i)
    {
        DoubleList lsw, lsh;
        for (int l = 0; l < d[i].count(); ++l)
        {
            for (int j = 0; j < d[i][l].count(); ++j)
            {
                lsw << d[i][l][j].width();
                lsh << d[i][l][j].height();
            }
        }
        widthByDataVariant << lsw;
        heightByDataVariant << lsh;
        countByVariant << lsw.count();
    }
}

DoubleList LowBounds::dff_1()
{
    return this->dff(1, 1000, 1, dff_1_func);
}

DoubleList LowBounds::dff_2()
{
    double p = 0.0001;
    return this->dff(0, 0.5 + p - eps, p, dff_2_func);
}

DoubleList LowBounds::dff_3()
{
    return this->dff(0, 0.5, 0.0001, dff_3_func);
}

DoubleList LowBounds::dff(double minParam, double maxParam, double plusParam, DffFunc func)
{
    DoubleList cnt, tmpwls, tmphls;
    double byk;
    double w, h, s;
    int cmp;
    for (int i = 0; i < variantCount; ++i)
    {
        byk = 0;
        for (double p = minParam; p < maxParam; p += plusParam)
        {
            s = 0;
            tmpwls.clear();
            tmphls.clear();

            for (int j = 0; j < countByVariant[i]; ++j)
            {
                w = isw[i] ? func(widthByDataVariant[i][j], p) : widthByDataVariant[i][j];
                h = ish[i] ? func(heightByDataVariant[i][j], p) : heightByDataVariant[i][j];
                s += w * h;

                tmpwls << w;
                tmphls << h;
            }
            if (s > byk)
            {
                byk = s;

                cmp = epsCompare(byk, dffMax);
                if (cmp > -1)
                {
                    dffMax = byk;
                }
                if (cmp == 1 || (!cmp && owls.count() > widthByDataVariant.count()))
                {
                    owls = widthByDataVariant[i];
                    wls = tmpwls;
                    ohls = heightByDataVariant[i];
                    hls = tmphls;
                }
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

double LowBounds::maximizeDff()
{
    int cnt = owls.count();
    double resw, resh;
    double square = 0;
    KnapsackSolver wslvr(owls, wls, 1.0);
    KnapsackSolver hslvr(ohls, hls, 1.0);

    for (int i = 0; i < cnt; ++i)
    {
        resw = 1.0 - wslvr.solve(i);
        resh = 1.0 - hslvr.solve(i);

        square += resw * resh;
    }
    return square;
}

double LowBounds::dffMaximum()
{
//    dffMax = this->maximizeDff();
    return dffMax;
}
