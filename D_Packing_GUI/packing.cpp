#include "packing.h"
#include "fragmentation.h"

#include <iostream>

using namespace std;

const double W = 1.5;
const double L = INT_MAX;

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

CortageList figuresToCortage(FigureList fs)
{
    CortageList res;

    for (int i = 0; i< fs.length(); ++i)
    {
        res.append(figureCortage(fs[i]));
    }

    return res;
}

TupleCoord packCortage(CortageList ls, FigureList fs)
{
    CortageXY xynull = ls[0];
    Cortage xres = xynull.first;
    Cortage yres = xynull.second;
    DoubleList xc, yc;
    xc.append(0.0);
    yc.append(0.0);

    Cortage newx, newy,  xcor, ycor, newxres, newyres;
    DoubleList cortXCoords, cortYCoords;
    double figx, figy;
    for (int i = 1; i < ls.count(); ++i)
    {
        xcor = ls[i].first;
        ycor = ls[i].second;
        cortXCoords = getCortageCoords(xres);
        cortYCoords = getCortageCoords(yres);

        int j = -1;
        int k = -1;
        int num = 0;
        do
        {
            if ((!num || !(num % 2)) && j < cortXCoords.count())
            {
                figx = -1.0;
                for (++j; j < cortXCoords.count(); ++j)
                {
                    if (j)
                    {
                        newx = shiftCortage(xcor, cortXCoords[j]);
                    }
                    else
                    {
                        newx = xcor;
                    }
                    newxres = sum(xres, newx);
                    if (checkSize(newxres, W, L))
                    {
                        figx = cortXCoords[j];
                        break;
                    }
                }
            }

            if ((!num || num % 2) && k < cortYCoords.count())
            {
                figy = -1.0;
                for (++k; k < cortYCoords.count(); ++k)
                {
                    if (k)
                    {
                        newy = shiftCortage(ycor, cortYCoords[k]);
                    }
                    else
                    {
                        newy = ycor;
                    }
                    newyres = sum(yres, newy);
                    if (checkSize(newyres, L, W))
                    {
                        figy = cortYCoords[k];
                        break;
                    }
                }
            }

            ++num;
        } while (!checkOverlap(fs, xc, yc, figx, figy, i)
                 && (j < cortXCoords.count() || k < cortYCoords.count()));
        if (checkOverlap(fs, xc, yc, figx, figy, i))
        {
            xc.append(figx);
            yc.append(figy);
            xres = newxres;
            yres = newyres;
        }
        if (figx < 0.0 || figy < 0.0)
        {
            xc.append(-1.0);
            yc.append(-1.0);
        }
    }
    return TupleCoord(xc, yc);
}

DoubleList getCortageCoords(Cortage cort)
{
    DoubleList res;
    res.append(0.0);
    for (int i = 0; i < cort.count(); ++i)
    {
        res.append(cort[i].first);
    }
    return res;
}

Cortage shiftCortage(Cortage c, double shift)
{
    Cortage res;
    res.append(TupleCoordLength(shift, 0.0));
    for (int i = 0; i < c.count(); ++i)
    {
        res.append(TupleCoordLength(shift + c[i].first, c[i].second));
    }
    return res;
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
    Cortage res(src);

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
                    res.insert(j, TupleCoordLength(ins[i].first, res[j].second));//0.0));
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

    return res;
}

// необходимое условие
bool checkSize(Cortage x, double w, double l)
{
    TupleCoordLength tx = x[x.count() - 1];

    bool bl = (epsCompare(tx.first, l) < 1);

    double maxw = 0.0;
    for (int i = 0; i < x.count(); ++i)
    {
        if (epsCompare(x[i].second, maxw) == 1)
        {
            maxw = x[i].second;
        }
    }
    bool bw = (epsCompare(maxw, w) < 1);

    return bw && bl;
}

// достаточное условие
bool checkOverlap(FigureList fs, DoubleList posx, DoubleList posy, double nx, double ny, int cnt)
{
    if (nx < 0.0 || ny < 0.0)
    {
        return false;
    }
    Figure checkingFigure = fs[cnt];
    Figure f;

    bool bxj, bxk, byj, byk;

    double xj, wj, yj, hj;
    double xk, wk, yk, hk;

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

                if (!(bxj || bxk || byj || byk))
                {
                    return false;
                }
            }
        }
    }

    return true;
}

double squarePacking(TupleCoord tc, FigureList fs)
{
    DoubleList x = tc.first;
    DoubleList y = tc.second;
    int cnt = fs.count(); // количество фигур и элементов в ч и у совпадает

    double w = 0.0;
    double h = 0.0;
    Figure f;
    QRectF r;
    double s;
    for (int i = 0; i < cnt; ++i)
    {
        if (x[i] >= 0.0 && y[i] >= 0.0)
        {
            f = fs[i];
            for (int j = 0; j < f.count(); ++j)
            {
                r = f[j];

                s = r.x() + r.width() + x[i];
                if (epsCompare(s, w))
                {
                    w = s;
                }

                s = r.y() + r.height() + y[i];
                if (epsCompare(s, h))
                {
                    h = s;
                }
            }
        }
    }
    return w * h;
}
