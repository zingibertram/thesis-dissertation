#include <QtCore/QCoreApplication>

#include "utils.h"
#include "lbounds.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PackingProblemData data;
    Figure f;
    if (!argc)
    {
        f = readFile(argv[0]);
    }
    else
    {
        f = readFile("data.in");
    }

    data = figureFragmentation(f);

    ListDouble dff1, dff2, dff3, dff4;

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
    cout << "/END of program";

    return a.exec();
}
