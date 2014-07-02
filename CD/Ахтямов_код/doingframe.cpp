#include "doingframe.h"
#include "ui_doingframe.h"

#include "utils.h"

DoingFrame::DoingFrame(QWidget *parent) :
    QDialog(parent, Qt::SplashScreen),
    ui(new Ui::DoingFrame)
{
    ui->setupUi(this);
}

DoingFrame::~DoingFrame()
{
    delete ui;
}

void DoingFrame::on_pushButton_Cancel_clicked()
{
    isCanceled = true;
}
