#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Start calcilating";
    t.start();
    ui->pushButton_Calculate->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Calculate_clicked()
{
    model.mainPacking();
    int ms = t.elapsed();
    QGraphicsScene *gsSrc0 = new QGraphicsScene();
    QGraphicsScene *gsSrc1 = new QGraphicsScene();
    QGraphicsScene *gsSrc2 = new QGraphicsScene();
    QGraphicsScene *gsRes = new QGraphicsScene();
    model.displaySource(gsSrc0, 0);
    model.displaySource(gsSrc1, 1);
    model.displaySource(gsSrc2, 2);
    model.displayResult(ui->tableWidget_Result, gsRes);
    ui->graphicsView_Source->setScene(gsSrc0);
    ui->graphicsView_Source_Min->setScene(gsSrc1);
    ui->graphicsView_Source_Max->setScene(gsSrc2);
    ui->graphicsView_Result->setScene(gsRes);
    qDebug() << "ALL working time" << ms;
}
