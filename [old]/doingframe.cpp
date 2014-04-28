#include "doingframe.h"
#include "ui_doingframe.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

DoingFrame::DoingFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DoingFrame)
{
    ui->setupUi(this);


    QGraphicsScene scene;

    QLabel *gifAnim = new QLabel();
    movie = new QMovie("D:\\projects\\qtcreator\\diploma\\D_Packing_GUI\\resources\\proc.gif");

    ui->label_2->setMovie(movie);

    scene.addWidget(gifAnim);
}

DoingFrame::~DoingFrame()
{
    delete ui;
}

void DoingFrame::show()
{
    movie->start();
    QWidget::show();
}

void DoingFrame::hide()
{
    movie->stop();
    QWidget::hide();
}
