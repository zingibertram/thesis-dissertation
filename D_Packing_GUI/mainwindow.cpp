#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_Calculate->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Calculate_clicked()
{
    model.mainPacking();
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
}
