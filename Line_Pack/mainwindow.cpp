#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <algorithm>

bool compare(int a, int b)
{
    return a > b;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_Calculate->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Calculate_clicked()
{
    ui->textBrowser_Results->clear();
    files.clear();

    disk = ui->spinBox->value();

    QStringList ls = ui->lineEdit->text().split(" ", QString::SkipEmptyParts);
    for (int i = 0; i < ls.count(); ++i)
    {
        int c = ls[i].toInt();
        files.append(c);
    }
    qSort(files.begin(), files.end(), compare);

    ui->textBrowser_Results->setText(this->calculate());
}

QString MainWindow::calculate()
{
    if (!files.count())
    {
        return "Files does not exist";
    }
    if (files[0] > disk)
    {
        return "Exist file bigger than disk";
    }

    int n = files.count();
    int *ds = new int [n];
    QList<QList<int> > resds;
    int i = 0;
    for (; i < n; ++i)
    {
        ds[i] = disk;
        resds.append(QList<int>());
        int j = 0;
        while (j < files.count())
        {
            if (files[j] <= ds[i])
            {
                ds[i] -= files[j];
                resds[i].append(files[j]);
                files.removeAt(j);
            }
            else
            {
                ++j;
            }
        }
        if (!files.count())
        {
            break;
        }
    }

    QString r;
    QString strres = "";
    for (int j = 0; j < resds.count(); ++j)
    {
        QString str = "";
        for (int k = 0; k < resds[j].count(); ++k)
        {
            str.append(r.setNum(resds[j][k]));
            str.append(" ");
        }
        str.append("\n");
        strres.append(str);
    }
    strres.append(QString("Number of disks is %1").arg(r.setNum(i + 1)));
    return strres;
}
