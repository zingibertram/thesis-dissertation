#ifndef DOINGFRAME_H
#define DOINGFRAME_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class DoingFrame;
}

class DoingFrame : public QDialog // окно, показываемое во время выполнения вычислений
{
    Q_OBJECT // макрос для использования специальных функций
    
public:
    explicit DoingFrame(QWidget *parent = 0); // конструктор
    ~DoingFrame(); // деструктор
    
private slots:
    void on_pushButton_Cancel_clicked(); // обработка нажатия кнопки

private:
    Ui::DoingFrame *ui; // элементы интерфейса
};

#endif // DOINGFRAME_H
