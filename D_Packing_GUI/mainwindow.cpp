#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    processFrame = new DoingFrame();
    label_sourceFile = new QLabel();
    model.newSource(":/input/resources/gen.in");

    this->connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    this->connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(action_Open_triggered()));
    this->connect(ui->action_DoBinary, SIGNAL(triggered()), this, SLOT(action_DoBinary_triggered()));
    this->connect(ui->action_DoSequentaly, SIGNAL(triggered()), this, SLOT(action_DoSequentaly_triggered()));
    this->connect(ui->pushButton_CalcBin, SIGNAL(clicked()), this, SLOT(action_DoBinary_triggered()));
    this->connect(ui->pushButton_CalcSeq, SIGNAL(clicked()), this, SLOT(action_DoSequentaly_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this);
    model.newSource(filename);
}

void MainWindow::action_DoBinary_triggered()
{
    this->calculate(BINARY);
}

void MainWindow::action_DoSequentaly_triggered()
{
    this->calculate(SEQUENCE);
}

void MainWindow::calculate(PackType t)
{
    isCanceled = false;

    this->setEnabled(false);
    processFrame->show();

    model.mainPacking(t);

    processFrame->hide();
    this->setEnabled(true);

    if (isCanceled)
    {
        QMessageBox::warning(this, "Calculation", "Calculation canceled");
    }
    else
    {
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
}
