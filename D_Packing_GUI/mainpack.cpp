#include "utils.h"
#include "lbounds.h"
#include "fragmentation.h"
#include "packing.h"
#include "mainpack.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

void mainPacking(char *filename)
{
    FigureList fs;
    fs = readFile(filename);

    lowBounds(fs);
    cout << "\nPACK square " << packing(fs) << endl;

    cout << "\n/END of program\n";
}

void lowBounds(FigureList fs)
{
    FigureVariantList data;
    data = figureFragmentation(fs);

    DoubleList dff1, dff2, dff3, dff4;

    //freopen("result.txt", "w", stdout);
    const int PRE = 7;
    const int WID = 10;
    cout.precision(PRE);
    dff1 = dff_1(data);
    cout << "DFF is u^(k)    ";
    for (int i = 0; i < dff1.count(); ++i)
    {
        cout << setw(WID) << dff1[i] << " ";
    }

    dff2 = dff_2(data);
    cout << "\nDFF is U^(eps)  ";
    for (int i = 0; i < dff2.count(); ++i)
    {
        cout << setw(WID) << dff2[i] << " ";
    }

    dff3 = dff_3(data);
    cout << "\nDFF is fi^(eps) ";
    for (int i = 0; i < dff3.count(); ++i)
    {
        cout << setw(WID) << dff3[i] << " ";
    }

    dff4 = dff_4(data);
    cout << "\nSimple square   ";
    for (int i = 0; i < dff4.count(); ++i)
    {
        cout << setw(WID) << dff4[i] << " ";
    }

    //fclose(stdout);
}

double packing(FigureList fs)
{
    CortageList corls = figuresToCortage(fs);
    TupleCoord tc = packCortage(corls, fs);
    double square = squarePacking(tc, fs);
    return square;
}
