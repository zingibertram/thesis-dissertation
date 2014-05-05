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
    Q_OBJECT // макрос для использования специальных функций
    
public:
    explicit MainWindow(QWidget *parent = 0); // конструктор
    ~MainWindow(); // деструктор
    
private slots: // обработчики событий
    void action_Open_triggered(); // открыть файл с входными данными
    void action_Save_triggered(); // сохранить результаты вычислений
    void action_DoBinary_triggered(); // выполнить вычисления, представив множество входных объектов в виде листьев двоичного дерева
    void action_DoSequentaly_triggered(); // упаковать все объекты последовательно
    void action_Generate_triggered(); // сгенерировать входные данные

private:
    void saveImage(QString name, QGraphicsScene *gs); // сохранение в файд name изображения со сцены gs
    void addGenerateAction(); // добавляет в меню подменю генератора входных данных
    void setControlsEnabled(bool enable); // блокировка/разблокировка некоторых элементов интерфейса
    void calculate(PackType t); // вычислить упаковку выбранным типом

    // элементы интерфейса
    Ui::MainWindow *ui;
    QLabel *label_sourceFile;
    QSpinBox *genCnt;

    Packing model; // модель упаковки
    DoingFrame *processFrame; // окно с кнопкой "Отмена"
};

#endif // MAINWINDOW_H
