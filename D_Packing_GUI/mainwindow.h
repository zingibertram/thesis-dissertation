#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainpack.h"

#include <QMainWindow>

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
    void on_pushButton_Calculate_clicked();

private:
    Ui::MainWindow *ui;
    Packing model;
};

#endif // MAINWINDOW_H
