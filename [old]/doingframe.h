#ifndef DOINGFRAME_H
#define DOINGFRAME_H

#include <QWidget>
#include <QMovie>
#include <QFrame>

namespace Ui {
class DoingFrame;
}

class DoingFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit DoingFrame(QWidget *parent = 0);
    ~DoingFrame();
    void show();
    void hide();
    
private:
    Ui::DoingFrame *ui;
    QMovie *movie;
};

#endif // DOINGFRAME_H
