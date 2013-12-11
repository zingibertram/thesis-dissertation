#include "figuregenerator.h"

#include <iomanip>
#include <math.h>
#include <time.h>

#include <QSet>
#include <QList>
#include <QPair>
#include <QRectF>
#include <QDebug>

FigureGenerator::FigureGenerator()
{
}

DoubleList FigureGenerator::generateDoubles(int cnt)
{
    DoubleList res;
    res.append(0.0);
    bool ok;
    for (int i = 0; i < cnt; ++i)
    {
        ok = generateUnequal(&res);
        qSort(res);
        if (!ok)
        {
            break;
        }
    }
    return res;
}

bool FigureGenerator::checkConnection(BoolGrid grid, int i, int j, int cx, int cy)
{
    bool n1, n2, n3, n4;
    bool dn1, dn2, dn3, dn4;
//    bool nn1, nn2, nn3, nn4;

    n1 = (0 < i) ? grid[i - 1][j] : false;
    n2 = (i < cx - 1) ? grid[i + 1][j] : false;
    n3 = (0 < j) ? grid[i][j - 1] : false;
    n4 = (j < cy - 1) ? grid[i][j + 1] : false;

//    nn1 = (1 < i) ? grid[i - 2][j] : false;
//    nn2 = (i < cx - 2) ? grid[i + 2][j] : false;
//    nn3 = (1 < j) ? grid[i][j - 2] : false;
//    nn4 = (j < cy - 2) ? grid[i][j + 2] : false;

    dn1 = (0 < i && j < cy - 1) ? grid[i - 1][j + 1] : false;
    dn2 = (i < cx - 1 && j < cy - 1) ? grid[i + 1][j + 1] : false;
    dn3 = (i < cx - 1 && 0 < j) ? grid[i + 1][j - 1] : false;
    dn4 = (0 < i && 0 < j) ? grid[i - 1][j - 1] : false;

    bool N1, N2, N3, N4;
    N1 = (n1 && n2) ? dn1 : true;
    N2 = (n2 && n3) ? dn2 : true;
    N3 = (n3 && n4) ? dn3 : true;
    N4 = (n4 && n1) ? dn4 : true;
//    N1 = (!n1 || (dn4 || nn1 || dn1));
//    N2 = (!n2 || (dn1 || nn2 || dn2));
//    N3 = (!n3 || (dn2 || nn3 || dn3));
//    N4 = (!n4 || (dn3 || nn4 || dn4));
    return N1 && N2 && N3 && N4;
}

Figure FigureGenerator::gridToFigure(BoolGrid grid, DoubleList x, DoubleList y, int ce)
{
    int cx = x.count() - 1;
    int cy = y.count() - 1;
    QSet<Position> possibleCells;
    for (int i = 0; i < cx; ++i)
    {
        possibleCells.insert(Position(i, 0));
        possibleCells.insert(Position(i, cy - 1));
    }
    for (int j = 1; j < cy - 1; ++j)
    {
        possibleCells.insert(Position(0, j));
        possibleCells.insert(Position(cx - 1, j));
    }

    QList<Position> posLs;
    int posIdx, i, j;
    Position pos;
    for (int k = 0; k < ce && possibleCells.count(); ++k)
    {
        posLs = possibleCells.toList();
//        qSort(posLs.begin(), posLs.end(), positionLess);
        posIdx = rand() % posLs.count();
        pos = posLs[posIdx];
        possibleCells.remove(pos);
        i = pos.first;
        j = pos.second;
        if (grid[i][j] && FigureGenerator::checkConnection(grid, i, j, cx, cy))
        {
//            if (!(j == 0 || j == cy - 1) && (i == 0 || i == cx - 1))
//            {
//                int tt = 90;
//                ++tt;
//            }
            grid[i][j] = false;
            if (0 < i)
            {
                possibleCells.insert(Position(i - 1, j));
            }
            if (i < cx - 1)
            {
                possibleCells.insert(Position(i + 1, j));
            }
            if (0 < j)
            {
                possibleCells.insert(Position(i, j - 1));
            }
            if (j < cy - 1)
            {
                possibleCells.insert(Position(i, j + 1));
            }
        }
    }

    Figure res;
    int b;
    for (i = 0; i < cx; ++i)
    {
        b = 0;
        for (j = 0; j < cy; ++j)
        {
            if (grid[i][j])
            {
                if (j == cy - 1)
                {
                    res.append(QRectF(x[i], y[b], x[i + 1] - x[i], y[j + 1] - y[b]));
                }
            }
            else
            {
                if (b == j)
                {
                    ++b;
                }
                else
                {
                    res.append(QRectF(x[i], y[b], x[i + 1] - x[i], y[j] - y[b]));
                    b = j;
                    --j;
                }
            }
        }
    }
    return res;
}

Figure FigureGenerator::generateFigure(int cx, int cy)
{
    DoubleList x = FigureGenerator::generateDoubles(cx);
    DoubleList y = FigureGenerator::generateDoubles(cy);

    cx = x.count() - 1;
    cy = y.count() - 1;
    int ce = ((double)(cx * cy) * 0.4);

    BoolGrid grid = new bool* [cx];
    for (int i = 0; i < cx; ++i)
    {
        grid[i] = new bool[cy];
        memset(grid[i], 1, sizeof(bool) * cy);
    }
    Figure res = FigureGenerator::gridToFigure(grid, x, y, ce);
    deleteGrid(grid, cx);
    return res;
}

FigureList FigureGenerator::generateSource(int cnt)
{
    srand((unsigned)clock());
    FigureList res;
    int cx, cy;
    for (int i = 0; i < cnt; ++i)
    {
        cx = rand () % 20 + 1;
        cy = rand () % 20 + 1;
        res.append(FigureGenerator::generateFigure(cx, cy));
    }
    return res;
}
