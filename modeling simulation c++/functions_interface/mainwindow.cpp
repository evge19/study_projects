#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget->legend->setVisible(true);
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    ui->widget->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    ui->widget->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    ui->widget->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);   // Включаем перетаскивание только по горизонтальной оси
    ui->widget->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
    ui->widget->xAxis->setLabel("ОX");
    ui->widget->yAxis->setLabel("ОY");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawButton_clicked()
{
    int a = ui->aEdit->text().toInt();
    int b = ui->bEdit->text().toInt();
    int c = ui->cEdit->text().toInt();
    int red = ui->redEdit->text().toInt();
    int green = ui->greenEdit->text().toInt();
    int blue = ui->blueEdit->text().toInt();
    int xmin = ui->xminEdit->text().toInt();
    int ymin = ui->yminEdit->text().toInt();
    int xmax = ui->xmaxEdit->text().toInt();
    int ymax = ui->ymaxEdit->text().toInt();

    QString str="y="+QString::number(a)+"x^2+"+QString::number(b)+"x+"+QString::number(c);
    double h = 0.01;
    int N=(xmax-xmin)/h + 2;

    QVector<double> x(N), y(N);
    int i=0;
    for (double X=xmin; X<=xmax; X+=h)
    {
        x[i] = X;
        y[i] = a*X*X+b*X+c;
        i++;
    }

    ui->widget->addGraph();

    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(red, green, blue, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setData(x, y);
    ui->widget->graph(ui->widget->graphCount()-1)->setName(str);




    ui->widget->xAxis->setRange(xmin, xmax);
    ui->widget->yAxis->setRange(ymin, ymax);

    ui->widget->replot();

}

void MainWindow::on_clearButton_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}

void MainWindow::draw()
{

}
