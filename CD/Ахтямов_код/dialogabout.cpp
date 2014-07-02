#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 64, 64);
    scene->addPixmap(QPixmap(":/img/resources/app.png").scaled(QSize(64, 64)));
    ui->graphicsView->setScene(scene);

    this->connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
