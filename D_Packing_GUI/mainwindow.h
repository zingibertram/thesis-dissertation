#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpack.h"
#include "doingframe.h"

#include <QMainWindow>
#include <QTime>
#include <QLabel>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void action_Open_triggered();
    void action_Save_triggered();
    void action_DoBinary_triggered();
    void action_DoSequentaly_triggered();
    void action_Generate_triggered();

private:
    void saveImage(QString name, QGraphicsScene *gs);
    void addGenerateAction();

    Ui::MainWindow *ui;
    Packing model;
    QTime t;
    DoingFrame *processFrame;
    QLabel *label_sourceFile;
    void calculate(PackType t);
    QSpinBox *genCnt;
};

#endif // MAINWINDOW_H
