#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QDateTime>
#include <QString>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->widget->legend->setVisible(true);
//    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   //ДСВ
{
    int a = ui->aEdit->text().toInt();
    int b = ui->bEdit->text().toInt();
    int alpha = ui->alphaEdit->text().toInt();
    int beta = ui->betaEdit->text().toInt();
    int n = ui->nEdit->text().toInt();
    int x, summ, y;
    float q;
    int N=b-a+1;
    QVector<double> c(N), d(N); //эксп
    double h = 1.0;
    int Q=b-a+1;
    QVector<double> s(Q), t(Q); //теория

    QVector<double> dispexp(n*N), dispesr(N); //дисперсия для суммы

    //теория
    for(double X=a; X<=b; X+=h)
    {
        s[X-a]=X;
        long int steor = 0;
        for(double Y = a; Y <= b; Y+=h)
        {
            if(X > Y)
                steor+=alpha*(X-Y);
            else
                steor+=beta*(Y-X);
        }
        t[X-a]=(steor*1.0/(b-a+1));

    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Теория");

    // эксп
    int uu=0;
    srand(time(0));
    for(x=a;x<b+1;x++) //x
    {
        c[uu]=x;
        summ=0;
        for(int j=0;j<n;j++)  //y
        {
            y=a+rand()%(b+1-a);
            if(x>y)
                q=alpha*(x-y);
            else
                q=beta*(y-x);
            dispexp[n*(x-a)+j]=q; // н раз

            summ=summ+q;
        }
        q=summ/(static_cast<float>(n));
        d[uu]=q;

        dispesr[uu]=q; // средняя оценка
        uu++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(c, d);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Эксперимент");

    //********************* минимум

    int mini=0;
    for (int i=1; i<t.size(); i++)
    {
        if (t[i]<t[mini])
            mini=i;
    }
    int maxi=0;
    for (int i=1; i<t.size(); i++)
    {
        if (t[i]>t[maxi])
            maxi=i;
    }

    QVector<double> fmin(1), gmin(1);
    fmin[0]=s[mini];
    gmin[0]=t[mini];

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(fmin, gmin);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Минимум");
    //************************ дисперсия
    QVector<double> fdispe(N), gdispe(N);
    float sum2;
    float disp;
    for(x=a;x<=b;x++) //x
    {
        fdispe[x-a]=x;
        sum2=0;
        for(int j=0;j<n;j++)  //y
        {
            sum2=sum2+(dispexp[n*(x-a)+j]-dispesr[x-a])*(dispexp[n*(x-a)+j]-dispesr[x-a]);
        }
        disp=sum2/(static_cast<float>(n-1));
        gdispe[x-a]=disp;
    }

//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setData(fdispe, gdispe);
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,255,0, 255));
//    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
//    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
//    ui->widget->graph(ui->widget->graphCount()-1)->setName("Дисперсия");

    //************************ сигма
    QVector<double> fsigma(N), gsigma(N);

    for(int i=0;i<N;i++) //x
    {
        fsigma[i]=fdispe[i];
        gsigma[i]=sqrt(gdispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(fsigma, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Сигма");

    ui->minEdit->setText(QString::number(t[mini]));
    ui->xminEdit->setText(QString::number(s[mini]));

    ui->widget->xAxis->setRange(a-0.2, b+0.2);
    ui->widget->yAxis->setRange(0, t[maxi]+0.5);

    ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked()  //ОЧИСТИТЬ
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}

void MainWindow::on_pushButton_3_clicked()  //НСВ
{
    int a = ui->aEdit->text().toInt();
    int b = ui->bEdit->text().toInt();
    int alpha = ui->alphaEdit->text().toInt();
    int beta = ui->betaEdit->text().toInt();
    int n = ui->nEdit->text().toInt();
    double x, summ, y, q;
    int N=b-a+1;
    QVector<double> c(N), d(N); //эксп
    double h = 0.01;
    int Q=(b-a)/h + 2;
    QVector<double> s(Q), t(Q); //теория

    QVector<double> dispexp(n*N), dispesr(N); //дисперсия для суммы

    //теория
    int k=0;
    for (double X=a; X<=b; X+=h)
    {
        s[k] = X;
        t[k] = alpha*(X-a)*(X-a)/(2*b-2*a)+beta*(b-X)*(b-X)/(2*b-2*a); //(beta/(2*(b-a)))*(X-a)*(X-a)+(alpha/(2*(b-a)))*(b-X)*(b-X)
        k++;

    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Теория");

    // эксп
    int uu=0;
    srand(time(0));
    for(x=a;x<b+1;x++) //x
    {
        c[uu]=x;
        summ=0;
        for(int j=0;j<n;j++)  //y
        {
            y=a+static_cast<double>(rand())/(static_cast<double>(RAND_MAX/(b-a)));
            if(x>y)
                q=alpha*(x-y);
            else
                q=beta*(y-x);
            dispexp[n*(x-a)+j]=q; // н раз
            summ=summ+q;
        }
        q=summ/(static_cast<double>(n));
        d[uu]=q;
        dispesr[uu]=q; // средняя оценка
        uu++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(c, d);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Эксперимент");

    //********************* минимум

    int mini=0;
    for (int i=1; i<t.size(); i++)
    {
        if (t[i]<t[mini])
            mini=i;
    }
    int maxi=0;
    for (int i=1; i<t.size(); i++)
    {
        if (t[i]>t[maxi])
            maxi=i;
    }

    QVector<double> fmin(1), gmin(1);
    fmin[0]=s[mini];
    gmin[0]=t[mini];

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(fmin, gmin);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Минимум");
    //************************ дисперсия
    QVector<double> fdispe(N), gdispe(N);
    float sum2;
    float disp;
    for(x=a;x<=b;x++) //x
    {
        fdispe[x-a]=x;
        sum2=0;
        for(int j=0;j<n;j++)  //y
        {
            sum2=sum2+(dispexp[n*(x-a)+j]-dispesr[x-a])*(dispexp[n*(x-a)+j]-dispesr[x-a]);
        }
        disp=sum2/(static_cast<double>(n-1));
        gdispe[x-a]=disp;
    }

//    ui->widget->addGraph();
//    ui->widget->graph(ui->widget->graphCount()-1)->setData(fdispe, gdispe);
//    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,255,0, 255));
//    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
//    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
//    ui->widget->graph(ui->widget->graphCount()-1)->setName("Дисперсия");

    //************************ сигма
    QVector<double> fsigma(N), gsigma(N);

    for(int i=0;i<N;i++) //x
    {
        fsigma[i]=fdispe[i];
        gsigma[i]=sqrt(gdispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(fsigma, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->widget->graph(ui->widget->graphCount()-1)->setName("Сигма");

    ui->minEdit->setText(QString::number(t[mini]));
    ui->xminEdit->setText(QString::number(s[mini]));

    ui->widget->xAxis->setRange(a-0.2, b+0.2);
    ui->widget->yAxis->setRange(0, t[maxi]+0.5);

    ui->widget->replot();

}
