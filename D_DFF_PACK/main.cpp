#include "utils.h"
#include "lbounds.h"
#include "fragmentation.h"
#include "packing.h"

#include <iostream>
#include <iomanip>
#include <stdio.h>

#include <QtCore/QCoreApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    FigureVariantList data;
    FigureList fs;
    char *filename = "data.in";
    fs = readFile(filename);

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
    cout << "\n/END of program\n";

//---------------------------------------------------------------

    CortageXY f1 = figureCortage(fs[0]);
    Cortage x1 = f1.first;
    Cortage y1 = f1.second;
    CortageXY f2 = figureCortage(fs[1]);
    Cortage x2 = f2.first;
    Cortage y2 = f2.second;
    Cortage res1 = insertCortage(x1, x2);
    Cortage res2 = insertCortage(x2, x1);
    Cortage sum_ = sum(res1, res2);

    return a.exec();
}
