#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

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
    QList<int> files;
    int disk;
    QString res;
    QString calculate();
};

#endif // MAINWINDOW_H
