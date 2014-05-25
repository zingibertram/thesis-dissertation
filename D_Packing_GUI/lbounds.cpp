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
    owls = 0;
    ohls = 0;
    hls.clear();
    dffMax = 0;
    subMax = 0;
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
    double h, s, tmpsub;
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
//                widthByDataVariant[i][j] = func(widthByDataVariant[i][j], p);
                s += widthByDataVariant[i][j] * h;

                tmpsub = h - heightByDataVariant[i][j];
                sub = tmpsub > sub ? tmpsub : sub;

                tmphls << h;
            }
            byk = s > byk ? s : byk;
            cmp = epsCompare(byk, dffMax);
            if (cmp > -1)
            {
                dffMax = byk;
                if (cmp == 1 || (!hls.count() || hls.count() > tmphls.count()))
                {
                    owls = i;
                    ohls = i;
                    hls = tmphls;
                }
            }
        }
//        dffMax = byk > dffMax ? byk : dffMax;
        cnt.append(byk);
    }
    return cnt;
}

double LowBounds::maximizeDff()
{
    int cnt = widthByDataVariant[owls].count();
    double resh, newh;
    double square = 0;
    KnapsackSolver hslvr(heightByDataVariant[ohls], hls, 1.0);

    qDebug() << "Maximize " << cnt << " bounds";
    for (int i = 0; i < cnt; ++i)
    {
        QApplication::processEvents();
        if (isCanceled)
        {
            isCanceled = false;
            break;
        }
        newh = 1.0 - hslvr.solve(i);
        resh = newh > hls[i] ? newh : hls[i];

        qDebug() << "Old " << hls[i] << "; new " << resh;

        square += widthByDataVariant[owls][i] * resh;
    }
    return square;
}

double LowBounds::dffMaximum(bool isMaximize)
{
    if (isMaximize)
    {
        double maximized = this->maximizeDff();
        dffMax = maximized > dffMax ? maximized : dffMax;
    }
    return dffMax;
}
