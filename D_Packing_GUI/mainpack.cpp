#include "utils.h"
#include "lbounds.h"
#include "mainpack.h"
#include "figuregenerator.h"

#include <time.h>

#include <QImage>
#include <QPainter>
#include <QTableWidgetItem>
#include <QTime>
#include <QDebug>

using namespace std;

Packing::Packing() :
    QObject(NULL)
{
    fCount = 0;
    stripWidth = 0;
    square = 0;
    stripLength = INT_MAX;
}

void Packing::mainPacking(PackType t)
{
    packing(t);
    emit this->packingEnd();
    lowBounds();
}

void Packing::lowBounds()
{
    QTime t;
    t.start();

    double xsc = 1.0 / (square / stripWidth);
    double ysc = 1.0 / stripWidth;
    data << pack.xCortToFig() << pack.yCortToFig();
    FigureVariantList dffData = data;
    QRectF r;
    for (int i = 0; i < dffData.count(); ++i)
    {
        for (int j = 0; j < dffData[i].count(); ++j)
        {
            for (int k = 0; k < dffData[i][j].count(); ++k)
            {
                r = dffData[i][j][k];
                dffData[i][j][k] = QRectF(r.x() * xsc, r.y() * ysc, r.width() * xsc, r.height() * ysc);
            }
        }
    }

    QList<bool> isw, ish;
    isw << true << true << true << false << true;
    ish << true << true << true << false << true;

    qDebug() << "Prepare to calc low bounds " << t.elapsed();
    t.start();

    LowBounds lb(dffData, isw, ish);
    dff1 = lb.dff_1();
    dff2 = lb.dff_2();
    dff3 = lb.dff_3();
    dff4 = lb.dff_4();
    qDebug() << "Alg end " << t.elapsed();
}

void Packing::packing(PackType t)
{
    pack = FigurePacking(source, grids, xGrid, yGrid, stripWidth, stripLength, figuresBound);

    switch (t)
    {
    case BINARY : pack.packBinaryTree(); break;
    case SEQUENCE : pack.pack(); break;
    }

    xCoor = pack.xPositions();
    yCoor = pack.yPositions();
    square = pack.squarePacking();
}

void Packing::displaySource(QGraphicsScene *gs, int fragIdx)
{
    double shift = 0.2;
    double y = 0.0;
    QRectF expanded;
    QPen b(Qt::black);
    QBrush g(QColor(0, 255, 127));
    QBrush r(QColor(255, 36, 0));
    double w = 0.0;
    for (int i = 0; i < fCount; ++i)
    {
        expanded = expand(figuresBound[i], MULT);
        expanded.moveTop(y * MULT);
        gs->addRect(expanded, b, g);
        displayFigure(gs, data[fragIdx][i], 0.0, y, MULT, b, r);
        y += figuresBound[i].height() + shift;
        if (figuresBound[i].width() > w)
        {
            w = figuresBound[i].width();
        }
    }
    gs->setSceneRect(0.0, 0.0, w * MULT, (y - shift) * MULT);
}

void Packing::displayRatioResult(QTableWidget *ratio)
{
    QString num;
    ratio->setRowCount(6);
    ratio->setColumnCount(dff1.count() + 1);
    ratio->setHorizontalHeaderItem(0, new QTableWidgetItem(TrRu::function));
    ratio->setHorizontalHeaderItem(1, new QTableWidgetItem(TrRu::sourceFrag));
    ratio->setHorizontalHeaderItem(2, new QTableWidgetItem(TrRu::minFrag));
    ratio->setHorizontalHeaderItem(3, new QTableWidgetItem(TrRu::maxFrag));
    ratio->setHorizontalHeaderItem(4, new QTableWidgetItem(TrRu::xCort));
    ratio->setHorizontalHeaderItem(5, new QTableWidgetItem(TrRu::yCort));
    ratio->setItem(0, 0, new QTableWidgetItem(TrRu::dff1));
    ratio->setItem(1, 0, new QTableWidgetItem(TrRu::dff2));
    ratio->setItem(2, 0, new QTableWidgetItem(TrRu::dff3));
    ratio->setItem(3, 0, new QTableWidgetItem(TrRu::dff4));
    ratio->setItem(4, 0, new QTableWidgetItem(TrRu::stripSquare));
    ratio->setItem(4, 1, new QTableWidgetItem(TrRu::stripSquareNum));
    ratio->setItem(5, 0, new QTableWidgetItem(TrRu::stripSquareReal));
    ratio->setItem(5, 1, new QTableWidgetItem(num.setNum(square)));
    for (int i = 0; i < dff1.count(); ++i)
    {
        ratio->setItem(0, i + 1, new QTableWidgetItem(num.setNum(dff1[i])));
        ratio->setItem(1, i + 1, new QTableWidgetItem(num.setNum(dff2[i])));
        ratio->setItem(2, i + 1, new QTableWidgetItem(num.setNum(dff3[i])));
        ratio->setItem(3, i + 1, new QTableWidgetItem(num.setNum(dff4[i])));
    }
    ratio->resizeColumnsToContents();
    ratio->resizeRowsToContents();
}

void Packing::displayCoordsResult(QTableWidget *coords)
{
    coords->setRowCount(fCount);
    coords->setColumnCount(2);

    coords->setHorizontalHeaderItem(0, new QTableWidgetItem(TrRu::x));
    coords->setHorizontalHeaderItem(1, new QTableWidgetItem(TrRu::y));

    QString num;
    for (int i = 0; i < fCount; ++i)
    {
        coords->setItem(i, 0, new QTableWidgetItem(num.setNum(xCoor[i])));
        coords->setItem(i, 1, new QTableWidgetItem(num.setNum(yCoor[i])));
    }
}

void Packing::displayResult(QTableWidget * ratio, QTableWidget *coord, QGraphicsScene *gs)
{
    this->displayRatioResult(ratio);
    this->displayCoordsResult(coord);

    double w, h;
    double width = 0.0;
    double height = 0.0;
    QPen b(Qt::black, 0);
    QRectF expanded;
    srand((unsigned)time(0));
    for (int i = 0; i < fCount; ++i)
    {
        if (xCoor[i] > -1 && yCoor[i] > -1)
        {
            QColor rndc = randColor();
            displayFigure(gs, source[i], xCoor[i], yCoor[i], MULT, b, QBrush(rndc));
            expanded = expand(figuresBound[i], MULT);
            w = expanded.x() + expanded.width() + xCoor[i] * MULT;
            if (w > width)
            {
                width = w;
            }
            h = expanded.y() + expanded.height() + yCoor[i] * MULT;
            if (h > height)
            {
                height = h;
            }
        }
    }
    gs->setSceneRect(0.0, 0.0, width + 1, stripWidth * MULT + 1);
    gs->addRect(QRectF(0.0, 0.0, width, stripWidth * MULT), b, QBrush(QColor(0, 0, 0, 0)));
}

void Packing::prepareSource()
{
    sortSource(&source, figureLessByHeight);
    sortSource(&source, figureLessByDensity);
    this->sourceIdxAccord();

    this->figuresRect();
    for (int i = 0; i < fCount; ++i)
    {
        if (figuresBound[i].height() >= figuresBound[i].width())
        {
            rotateFigure(&source[i]);
        }
    }
    this->figuresRect();
}

void Packing::clear()
{
    for (int i = 0; i < grids.count(); ++i)
    {
        deleteGrid(grids[i], xGrid[i].count() - 1);
    }

    source.clear();
    figuresBound.clear();
    data.clear();
    grids.clear();
    xGrid.clear();
    yGrid.clear();
    xCoor.clear();
    yCoor.clear();
    dff1.clear();
    dff2.clear();
    dff3.clear();
    dff4.clear();
    input.clear();
    sourceReshuffle.clear();

    fCount = 0;
    stripWidth = 0;
    square = 0;
    stripLength = INT_MAX;
}

void Packing::newSource(QString filename)
{
    this->clear();
    this->readFile(filename);
    this->prepareSource();
    this->figureFragmentation();
}

void Packing::generateSource(QString filename, int cnt)
{
    FigureList gen = FigureGenerator::generateSource(cnt);

    this->saveGeneratedSource(filename, gen);
}

void Packing::sourceIdxAccord()
{
    for (int i = 0; i < fCount; ++i)
    {
        sourceReshuffle << i;
        for (int j = 0; j < fCount; ++j)
        {
            if (input[i] == source[j])
            {
                sourceReshuffle[i] = j;
                break;
            }
        }
    }
}

int Packing::sourceCount()
{
    return fCount;
}
