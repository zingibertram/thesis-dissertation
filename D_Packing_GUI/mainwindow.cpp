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
    QGraphicsScene *gsSrc = new QGraphicsScene();
    QGraphicsScene *gsRes = new QGraphicsScene();
    model.displaySource(gsSrc);
    model.displayResult(ui->tableWidget_Result, gsRes);
    ui->graphicsView_Source->setScene(gsSrc);
    ui->graphicsView_Result->setScene(gsRes);
}
