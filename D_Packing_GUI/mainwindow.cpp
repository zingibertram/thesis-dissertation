#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translation.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QDir>
#include <QWidgetAction>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget_Coords->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Result->setEditTriggers(QAbstractItemView::NoEditTriggers);

    processFrame = new DoingFrame(this);
    label_sourceFile = new QLabel();
    model.newSource(TrRu::defaultSource);
    this->addGenerateAction();

    this->connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    this->connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(action_Open_triggered()));
    this->connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(action_Save_triggered()));
    this->connect(ui->action_DoBinary, SIGNAL(triggered()), this, SLOT(action_DoBinary_triggered()));
    this->connect(ui->action_DoSequentaly, SIGNAL(triggered()), this, SLOT(action_DoSequentaly_triggered()));
    this->connect(ui->action_Gen, SIGNAL(triggered()), this, SLOT(action_Generate_triggered()));
    this->connect(ui->pushButton_CalcBin, SIGNAL(clicked()), this, SLOT(action_DoBinary_triggered()));
    this->connect(ui->pushButton_CalcSeq, SIGNAL(clicked()), this, SLOT(action_DoSequentaly_triggered()));
    this->connect(&model, SIGNAL(packingEnd()), processFrame, SLOT(hide()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_Open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, TrRu::openDlgHead, QString(), TrRu::dataFiles);
    model.newSource(filename);

    ui->tableWidget_Coords->clear();
    ui->tableWidget_Result->clear();

    ui->graphicsView_Result->setScene(NULL);
    ui->graphicsView_Source->setScene(NULL);
    ui->graphicsView_Source_Max->setScene(NULL);
    ui->graphicsView_Source_Min->setScene(NULL);
}

void MainWindow::saveImage(QString name, QGraphicsScene *gs)
{
    QImage img(gs->sceneRect().size().toSize(), QImage::Format_ARGB32);
    QPainter p(&img);
    gs->render(&p);
    p.end();
    img.save(name);
}

void MainWindow::action_Save_triggered()
{
    QString dirname = QFileDialog::getExistingDirectory(this, TrRu::saveResDir);

    model.saveResult(QDir(dirname).filePath(TrRu::resultDatFile));

    this->saveImage(QDir(dirname).filePath(TrRu::sourceMinImgFile), ui->graphicsView_Source_Min->scene());
    this->saveImage(QDir(dirname).filePath(TrRu::sourceMaxImgFile), ui->graphicsView_Source_Max->scene());
    this->saveImage(QDir(dirname).filePath(TrRu::sourceImgFile), ui->graphicsView_Source->scene());
    this->saveImage(QDir(dirname).filePath(TrRu::resultImgFile), ui->graphicsView_Result->scene());
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
    if (model.sourceCount() == 0)
    {
        QMessageBox::warning(this, TrRu::error, TrRu::damagedCalc);
        return;
    }

    isCanceled = false;

    this->setControlsEnabled(false);

    model.mainPacking(t);

    this->setControlsEnabled(true);

    if (isCanceled)
    {
        QMessageBox::warning(this, TrRu::cancel, TrRu::calcCancel);
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
        model.displayResult(ui->tableWidget_Result, ui->tableWidget_Coords, gsRes);

        ui->graphicsView_Source->setScene(gsSrc0);
        ui->graphicsView_Source_Min->setScene(gsSrc1);
        ui->graphicsView_Source_Max->setScene(gsSrc2);
        ui->graphicsView_Result->setScene(gsRes);
    }
}

void MainWindow::action_Generate_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, TrRu::saveGenDir, QString(), TrRu::dataFiles);

    this->setControlsEnabled(false);

    int num = 5;
    if (genCnt != NULL)
    {
        num = genCnt->value();
    }
    model.generateSource(filename, num);

    this->setControlsEnabled(true);
}

void MainWindow::addGenerateAction()
{
    genCnt = new QSpinBox();
    genCnt->setMaximum(30);
    genCnt->setMinimum(1);
    genCnt->setValue(5);

    QWidgetAction *wa = new QWidgetAction(this);
    wa->setDefaultWidget(genCnt);

    ui->menu_Generate->addAction(wa);
}

void MainWindow::setControlsEnabled(bool enable)
{
    if (enable)
    {
        processFrame->hide();
    }
    ui->pushButton_CalcBin->setEnabled(enable);
    ui->pushButton_CalcSeq->setEnabled(enable);
    ui->menubar->setEnabled(enable);
    if (!enable)
    {
        processFrame->show();
    }
}
