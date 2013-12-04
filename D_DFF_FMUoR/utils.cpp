#include "utils.h"

#include <stdio.h>
#include <iostream>

using namespace std;

const QRectF sep = QRectF(-1.0, -1.0, 0.0, 0.0);

Figure readFile(char *filename)
{
    freopen(filename, "r", stdin);
    int num;
    cin >> num;
    double k, x, y, w, h;
    Figure f;
    for (int i = 0; i < num; ++i)
    {
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            cin >> x >> y >> w >> h;
            f.append(QRectF(x, y, w, h));
        }
        f.append(sep);
    }
    return f;
}
