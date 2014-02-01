#include "utils.h"
#include "lbounds.h"
#include "packing.h"
#include "mainpack.h"
#include "figuregenerator.h"

#include <iostream>
#include <stdio.h>
#include <time.h>

#include <QImage>
#include <QPainter>

using namespace std;

Packing::Packing(char *filename)
{
    this->readFile(filename);
//    source = FigureGenerator::generateSource(16);
//    this->saveSource();
    sortSource(&source);
    fCount = source.count();
    stripWidth = 1.5;
    stripLength = INT_MAX;
    this->figureFragmentation();
    this->figuresRect();
}

void Packing::saveSource()
{
    freopen("gen.out", "w", stdout);
    cout << source.count() << endl;
    for (int f = 0; f < source.count(); ++f)
    {
        Figure ortho = source[f];
        cout << ortho.count() << endl;
        for (int r = 0; r < ortho.count(); ++r)
        {
            QRectF rect = ortho[r];
            cout << rect.x() << " " << rect.y()  << " " << rect.width()  << " " << rect.height() << endl;
        }
    }
    fclose(stdout);
}

void Packing::readFile(char *filename)
{
    source.clear();
    freopen(filename, "r", stdin);
    int num;
    cin >> num;
    double k, x, y, w, h;
    Figure f;
    for (int i = 0; i < num; ++i)
    {
        f.clear();
        cin >> k;
        for (int j = 0; j < k; ++j)
        {
            cin >> x >> y >> w >> h;
            f.append(QRectF(x, y, w, h));
        }
        source.append(f);
    }
    cin >> stripWidth;
}

void Packing::mainPacking()
{
    lowBounds();
    packing();
}

void Packing::lowBounds()
{
    LowBounds lb(data);
    dff1 = lb.dff_1();
    dff2 = lb.dff_2();
    dff3 = lb.dff_3();
    dff4 = lb.dff_4();
}

void Packing::packing()
{
    FigurePacking pack(source, grids, xGrid, yGrid, stripWidth, stripLength);
    pack.pack();
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
    QPen rp(QColor(255, 36, 0));
    for (int i = 0; i < fCount; ++i)
    {
        expanded = expand(figuresBound[i], MULT);
        expanded.moveTop(y * MULT);
        gs->addRect(expanded, b, g);
        displayFigure(gs, data[fragIdx][i], 0.0, y, MULT, b, r);
        y += figuresBound[i].height() + shift;
    }
    gs->setSceneRect(0.0, 0.0, stripWidth * MULT, (y - shift) * MULT);
    gs->addRect(gs->sceneRect(), b, QBrush(QColor(0, 0, 0, 0)));

    QImage img(gs->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter p(&img);
    gs->render(&p);
    p.end();
    QString num;
    img.save(QString("source%1.png").arg(num.setNum(fragIdx)));
}

void Packing::displayResult(QTableWidget *tw, QGraphicsScene *gs)
{
    QString num;
    tw->setRowCount(5);
    tw->setColumnCount(data.count() + 1);
    tw->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("Функция")));
    tw->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("Исходное разбиение")));
    tw->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("Минимальное разбиение")));
    tw->setHorizontalHeaderItem(3, new QTableWidgetItem(QString::fromLocal8Bit("Максимальное разбиение")));
    tw->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("u^(k)")));
    tw->setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("fi^eps")));
    tw->setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("U^eps")));
    tw->setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("Площадь")));
    tw->setItem(4, 0, new QTableWidgetItem(QString::fromLocal8Bit("Площадь полосы")));
    tw->setItem(4, 1, new QTableWidgetItem(num.setNum(square)));
    for (int i = 0; i < data.count(); ++i)
    {
        tw->setItem(0, i + 1, new QTableWidgetItem(num.setNum(dff1[i])));
        tw->setItem(1, i + 1, new QTableWidgetItem(num.setNum(dff2[i])));
        tw->setItem(2, i + 1, new QTableWidgetItem(num.setNum(dff3[i])));
        tw->setItem(3, i + 1, new QTableWidgetItem(num.setNum(dff4[i])));
    }

    double w, h;
    double width = 0.0;
    double height = 0.0;
    QPen b(Qt::black);
    QRectF expanded;
    srand((unsigned)time(0));
    for (int i = 0; i < fCount; ++i)
    {
        if (epsCompare(xCoor[i], 0.0) > -1 && epsCompare(yCoor[i], 0.0) > -1)
        {
            QColor rndc = randColor();
            displayFigure(gs, source[i], xCoor[i], yCoor[i], MULT, b/*QPen(rndc)*/, QBrush(rndc));
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
    gs->setSceneRect(0.0, 0.0, width, stripWidth * MULT);
    gs->addRect(gs->sceneRect(), b, QBrush(QColor(0, 0, 0, 0)));

    QImage img(gs->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter p(&img);
    gs->render(&p);
    p.end();
    img.save("result.png");
}
