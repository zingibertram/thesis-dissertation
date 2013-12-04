#include "packing.h"
#include "fragmentation.h"

#include <iostream>

using namespace std;

CortageXY figureCortage(Figure f)
{
    ListXY xy = gridNodes(f);
    DoubleList x = xy.first;
    DoubleList y = xy.second;
    Quantum q = quantumFragmentation(xy, f);
    BoolGrid grid = q.second;

    Cortage cortx;
    for (int i = 0; i < x.count() - 1; ++i)
    {
        double xi = x[i + 1];
        double h = 0.0;
        for (int j = 0; j < y.count() - 1; ++j)
        {
            if (grid[i][j])
            {
                h += y[j + 1] - y[j];
            }
        }
        cortx.append(TupleCoordLength(xi, h));
    }
    Cortage corty;
    for (int i = 0; i < y.count() - 1; ++i)
    {
        double w = 0.0;
        double yi = y[i + 1];
        for (int j = 0; j < x.count() - 1; ++j)
        {
            if (grid[j][i])
            {
                w += x[j + 1] - x[j];
            }
        }
        corty.append(TupleCoordLength(yi, w));
    }

    return CortageXY(cortx, corty);
}

Cortage sum(Cortage c1, Cortage c2)
{
    Cortage res;

    int cnt1 = c1.count();
    int cnt2 = c2.count();
    if (!cnt1 && !cnt2)
    {
        return res;
    }
    else
    {
        if (cnt1 && !cnt2)
        {
            return c1;
        }
        if (!cnt1 && cnt2)
        {
            return c2;
        }
    }

    Cortage insc1 = insertCortage(c1, c2);
    Cortage insc2 = insertCortage(c2, c1);
    if (insc1.count() != insc2.count())
    {
        cout << "WARNING: different inserting!" << endl;
    }
    for (int i = 0; i < insc1.count(); ++i)
    {
        if (tupleCompare(insc1[i], insc2[i]))
        {
            cout << "WARNING: not equal! " << i << endl;
        }
        res.append(TupleCoordLength(insc1[i].first, insc1[i].second + insc2[i].second));
    }
//    printCortage(res);

    return res;
}

Cortage insertCortage(Cortage src, Cortage ins)
{
    Cortage res = src;

    // сделать линейной
    int cmp;
    for (int i = 0; i < ins.count(); ++i)
    {
        for (int j = 0; j < res.count(); ++j)
        {
            cmp = tupleCompare(ins[i], res[j]);
            if (!cmp)
            {
                break;
            }
            else
            {
                if (cmp == -1)
                {
                    res.insert(j, TupleCoordLength(ins[i].first, 0.0));
                    break;
                }
                else
                {
                    if (j == res.count() - 1)
                    {
                        res.insert(j + 1, TupleCoordLength(ins[i].first, 0.0));
                        break;
                    }
                }
            }
        }
    }

    int prev = res.count() - 1;
    for (int i = res.count() - 2; i >= 0 ; --i)
    {
        if (epsCompare(res[i].second, 0.0))
        {
            prev = i;
        }
        else
        {
            if (epsCompare(res[prev].second, 0.0))
            {
                res[i].second = res[prev].second;
            }
        }
    }

    return res;
}

// необходимое условие
bool checkSize(Cortage x, Cortage y, double w, double l)
{
    TupleCoordLength tx = x[x.count() - 1];
    TupleCoordLength ty = y[y.count() - 1];

    bool xl = (epsCompare(tx.first, l) < 1);
    bool yw = (epsCompare(ty.first, w) < 1);

    double maxw = 0.0;
    for (int i = 0; i < x.count(); ++i)
    {
        if (epsCompare(x[i].second, maxw) == 1)
        {
            maxw = x[i].second;
        }
    }
    bool xw = (epsCompare(maxw, w) < 1);

     maxw = 0.0;
    for (int i = 0; i < y.count(); ++i)
    {
        if (epsCompare(y[i].second, maxw) == 1)
        {
            maxw = y[i].second;
        }
    }
    bool yl = (epsCompare(maxw, l) < 1);

    return xl && yw && xw && yl;
}

// достаточное условие
bool checkOverlap(FigureList fs, DoubleList posx, DoubleList posy, double nx, double ny, int cnt)
{
    if (!(posx.count() == posy.count() && posy.count() == cnt))
    {
        return false;
    }

    Figure checkingFigure = fs[cnt];
    Figure f;

    bool bxj, bxk, byj, byk;

    double xj, yj, wj, hj;
    double xk, yk, wk, hk;

    QRectF rj, rk;

    for (int i = 0; i < cnt; ++i)
    {
        f = fs[i];
        for (int j = 0; j < checkingFigure.count(); ++j)
        {
            rj = checkingFigure[j];
            xj = rj.x() + nx;
            yj = rj.y() + ny;
            wj = rj.width();
            hj = rj.height();
            for (int k = 0; k < f.count(); ++k)
            {
                rk = f[k];
                xk = rk.x() + posx[i];
                yk = rk.y() + posy[i];
                wk = rk.width();
                hk = rk.height();

                bxj = (epsCompare(xj, xk + wk) > -1);
                bxk = (epsCompare(xk, xj + wj) > -1);
                byj = (epsCompare(yj, yk + hk) > -1);
                byk = (epsCompare(yk, yj + hj) > -1);

                if (!((bxj || bxk) && (byj || byk)))
                {
                    return false;
                }
            }
        }
    }

    return true;
}
