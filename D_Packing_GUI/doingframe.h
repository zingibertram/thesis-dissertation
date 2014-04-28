#ifndef DOINGFRAME_H
#define DOINGFRAME_H

#include <QWidget>

namespace Ui {
class DoingFrame;
}

class DoingFrame : public QWidget
{
    Q_OBJECT
    
public:
    explicit DoingFrame(QWidget *parent = 0);
    ~DoingFrame();
    
private slots:
    void on_pushButton_Cancel_clicked();

private:
    Ui::DoingFrame *ui;
};

#endif // DOINGFRAME_H
