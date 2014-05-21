#include "lbounds.h"

#include <math.h>

#include <QApplication>
#include <QDebug>

using namespace std;

LowBounds::LowBounds(DoubleGrid w, DoubleGrid h, IntList cnt)
{
    dffMax = 0;
    countByVariant = cnt;
    variantCount = countByVariant.count();
    widthByDataVariant = w;
    heightByDataVariant = h;
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
    DoubleList cnt, tmphls;
    double byk;
    double h, s;
    int cmp;
    double sub = 0;
    for (int i = 0; i < variantCount; ++i)
    {
        byk = 0;
        for (double p = minParam; p < maxParam; p += plusParam)
        {
            s = 0;
            tmphls.clear();
            for (int j = 0; j < countByVariant[i]; ++j)
            {
                h = func(heightByDataVariant[i][j], p);
                s += widthByDataVariant[i][j] * h;
//                sub = fabs(h - heightByDataVariant[i][j]) > sub ? fabs(h - heightByDataVariant[i][j]) : sub;
                sub = heightByDataVariant[i][j] > sub ? heightByDataVariant[i][j] : sub;

                tmphls << h;
            }
            if (s > byk)
            {
                byk = s;

                cmp = epsCompare(sub, dffMax);
                if (cmp > -1)
                {
                    dffMax = sub;
                    owls = widthByDataVariant[i];
                    ohls = heightByDataVariant[i];
                    hls = tmphls;
                }
//                if (cmp == 1 || (!cmp && owls.count() > widthByDataVariant.count()))
//                {
//                    owls = widthByDataVariant[i];
//                    ohls = heightByDataVariant[i];
//                    hls = tmphls;
//                }
            }
        }
        cnt.append(byk);
    }
    return cnt;
}

double LowBounds::maximizeDff()
{
    int cnt = owls.count();
    double resh, newh;
    double square = 0;
    KnapsackSolver hslvr(ohls, hls, 1.0);

    qDebug() << "Maximize " << cnt << " bounds";
    for (int i = 0; i < cnt; ++i)
    {
        QApplication::processEvents();
        if (isCanceled)
        {
            isCanceled = false;
            break;
        }
        resh = 1.0 - hslvr.solve(i);
//        resh = newh > hls[i] ? newh : hls[i];

        qDebug() << "Old " << hls[i] << "; new " << resh;

        square += owls[i] * resh;
    }
    return square;
}

double LowBounds::dffMaximum(bool isMaximize)
{
    if (isMaximize)
    {
        dffMax = this->maximizeDff();
    }
    return dffMax;
}
