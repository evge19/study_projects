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
}

MainWindow::~MainWindow()
{
    delete ui;
}
double s_rand() { return rand() + 1E-10; }
double MainWindow::tauerl1(double po1, int r1)
{
    double sumt=0;
    for(int ri=0;ri<r1;ri++)
    {
        sumt=sumt+log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));
    }
    sumt=sumt*(-1)/(po1*r1);
    return sumt;
}

double MainWindow::tauerl2(int r1)
{
    double sumt=0;
    for(int ri=0;ri<r1;ri++)
    {
        sumt=sumt+log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));
    }
    sumt=sumt*(-1)/r1;
    return sumt;
}
void MainWindow::on_pushButton_clicked()
{
    int n = ui->nEdit->text().toInt();
    int m = ui->mEdit->text().toInt();
    int pomax = ui->pomaxEdit->text().toDouble();

    //****************** теория
    double h = 0.01;
    int Q=(pomax-0)/h + 2;
    QVector<double> s(Q), t(Q); //теория
    int qmax=pomax*5+1;
    int dlpo=0;
    int counter=0;
    QVector<double> prmx(Q), prmy(Q);
    int j=0;
    for (double X=0; X<=pomax; X+=h)
    {
        prmx[j] = X;
        prmy[j] = m+1;
        j++;
    }
    for (double x=0; x<=pomax; x+=h)
    {
        s[counter] = x;
        if(dlpo==100)
        {
            t[counter]=(m+1)/(static_cast<double>(2));
        }
        else
            t[counter] = x*(1-(m+2-m*x-x)*pow(x,m+1))/(1-pow(x,m+2))/(1-x);
        counter++;
        dlpo++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(prmx, prmy);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));

    //******************** эксп
    QVector<double> dispe(qmax); //дисперсия для суммы
    QVector<double> ksr(qmax), k, celpo(qmax);  // среднее
    double sumd, po;
    int uu=0;
    //tttttt
    double tau1, tau2;
    bool busy;
    int amountQueue, summApll, amountApll;
    //ttttt
    srand(time(0));
    for(po=0; po <=pomax+0.1; po=po+0.2)
    {
        celpo[uu]=po;
        sumd=0;
        busy = false;  // занятость канала обработки
        amountQueue = 0 ; // количество заявок в очереди
        summApll = 0;  // среднее количество заявок - наше К

        if(po==0)
            ksr[uu]=0;
        else
        {
            tau1 = float(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0)))); // время прихода новой заявки
            tau2 = 0;  // время обработки заявки

            for(double ch = 0; ch < n; ch++)
            {
                amountApll = 0; // счетчик обслуженных заявок
                while(amountApll < 10)
                {
                    if(tau1==0)  // если заявка пришла в систему за время tau1
                    {
                        qDebug()<<"hjhhhh"<<tau1;
                        if(amountQueue==0 && tau2==0){  // если очередь пуста И никого не обрабатывают
                            tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0)))); // задается время прихода новой зявки
                            tau2 = -log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // задается время обработки текущей заявки
                            busy = true;
                        }
                        else
                        { //если очередь пуста ИЛИ никого не обрабатывают
                            if (amountQueue < (m+1)){  // если в очереди есть место и кого-то обрабатывают
                                amountQueue += 1;  // помещаем текущую заявку в очередь
                                tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // задаем время прихода новой заявки
                            }
                            else  // если в очереди места нет
                                tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // выкидываем заявку в поток отказа и ждем новую заявку
                        }
                    }
                    if (tau2==0) // если чувак обработался
                    {
                        if (amountQueue > 0)
                        {  // если в очереди кто-то есть
                            amountQueue -= 1 ; // заявка из очереди переходит в пункт обработки
                            tau2 = -log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // задаем время обработки этой заявки
                            busy = true;  // пункт обработки занят
                        }
                        else
                            busy = false; // пункт обработки не занят
                    }
                    if (busy==true)  // если в пункте обработки есть заявка
                    {
                        if (tau1 >= tau2)  // если время прихода новой заявки больше чем время обработки текущей заявки
                        {
                            tau1 -= tau2;
                            tau2 -= tau2;
                        }
                        else if (tau2 >= tau1)
                        {
                            tau2 -= tau1;
                            tau1 -= tau1;
                        }
                    }
                    else
                        tau1 = 0;

                    if(tau2==0 && busy==true)
                    {
                        amountApll += 1;
                        if (amountApll == 10)
                        {
                            summApll += amountQueue;
                            break;
                        }
                        busy = false;
                    }

                }
                k.append(amountQueue);
            }
        }

        ksr[uu]=(double(summApll)/double(n));

        for(int j=0;j<k.size();j++)  //дисперсия
        {
            sumd=sumd+(k[j]-ksr[uu])*(k[j]-ksr[uu]);
        }
        dispe[uu]=sumd/(static_cast<double>(k.size()-1));

        k.clear();

        uu++;
    }
    // эксперимент
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, ksr);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    //************************ сигма
    QVector<double>  gsigma(qmax);

    for(int i=0;i<qmax;i++) //x
    {
        gsigma[i]=sqrt(dispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    ui->widget->xAxis->setRange(-0.1+0, pomax+0.1);
    ui->widget->yAxis->setRange(-0.3+0,m+2);

    ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->replot();
}

void MainWindow::on_pushButton_rm_clicked()
{
    int n = ui->nEdit->text().toInt();
    int m = ui->mEdit->text().toInt();
    int pomax = ui->pomaxEdit->text().toInt();
    int r = ui->rEdit->text().toInt();

    //****************** теория
    double h = 0.01;
    int Q=(pomax-0)/h + 2;
    QVector<double> s(Q), t(Q); //теория
    int qmax=pomax*5+1;
    int dlpo=0;
    int counter=0;
    QVector<double> prmx(Q), prmy(Q);
    int j=0;
    for (double X=0; X<=pomax; X+=h)
    {
        prmx[j] = X;
        prmy[j] = m+1;
        j++;
    }
    for (double x=0; x<=pomax; x+=h)
    {
        s[counter] = x;
        if(dlpo==100)
        {
            t[counter]=(m+1)/(static_cast<double>(2));
        }
        else
            t[counter] = x*(1-(m+2-m*x-x)*pow(x,m+1))/(1-pow(x,m+2))/(1-x);
        counter++;
        dlpo++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(prmx, prmy);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));

    //******************** эксп
    QVector<double> dispe(qmax); //дисперсия для суммы
    QVector<double> ksr(qmax), k, celpo(qmax);  // среднее
    double sumd, po;
    int uu=0;
    //tttttt
    double tau1, tau2;
    bool busy;
    int amountQueue, summApll, amountApll;
    //ttttt
    srand(time(0));
    for(po=0; po <=pomax+0.1; po=po+0.2)
    {
        celpo[uu]=po;
        sumd=0;
        busy = false;  // занятость канала обработки
        amountQueue = 0 ; // количество заявок в очереди
        summApll = 0;  // среднее количество заявок - наше К

        if(po==0)
            ksr[uu]=0;
        else
        {
            tau1 = tauerl1(po, r); // время прихода новой заявки
            tau2 = 0;  // время обработки заявки

            for(double ch = 0; ch < n; ch++)
            {
                amountApll = 0; // счетчик обслуженных заявок
                while(amountApll < 10)
                {
                    if(tau1==0)  // если заявка пришла в систему за время tau1
                    {
                        if(amountQueue==0 && tau2==0){  // если очередь пуста И никого не обрабатывают
                            tau1 = tauerl1(po, r); // задается время прихода новой зявки
                            tau2 = -log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0.0001))));  // задается время обработки текущей заявки
                            busy = true;
                        }
                        else
                        { //если очередь пуста ИЛИ никого не обрабатывают
                            if (amountQueue < (m+1)){  // если в очереди есть место и кого-то обрабатывают
                                amountQueue += 1;  // помещаем текущую заявку в очередь
                                tau1 = tauerl1(po, r);  // задаем время прихода новой заявки
                            }
                            else  // если в очереди места нет
                                tau1 = tauerl1(po, r);  // выкидываем заявку в поток отказа и ждем новую заявку
                        }
                    }
                    if (tau2==0) // если чувак обработался
                    {
                        if (amountQueue > 0)
                        {  // если в очереди кто-то есть
                            amountQueue -= 1 ; // заявка из очереди переходит в пункт обработки
                            tau2 = -log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // задаем время обработки этой заявки
                            busy = true;  // пункт обработки занят
                        }
                        else
                            busy = false; // пункт обработки не занят
                    }
                    if (busy==true)  // если в пункте обработки есть заявка
                    {
                        if (tau1 >= tau2)  // если время прихода новой заявки больше чем время обработки текущей заявки
                        {
                            tau1 -= tau2;
                            tau2 -= tau2;
                        }
                        else if (tau2 >= tau1)
                        {
                            tau2 -= tau1;
                            tau1 -= tau1;
                        }
                    }
                    else
                        tau1 = 0;

                    if(tau2==0 && busy==true)
                    {
                        amountApll += 1;
                        if (amountApll == 10)
                        {
                            summApll += amountQueue;
                            break;
                        }
                        busy = false;
                    }

                }
                k.append(amountQueue);
            }
        }

        ksr[uu]=(double(summApll)/double(n));

        for(int j=0;j<k.size();j++)  //дисперсия
        {
            sumd=sumd+(k[j]-ksr[uu])*(k[j]-ksr[uu]);
        }
        dispe[uu]=sumd/(static_cast<double>(k.size()-1));

        k.clear();

        uu++;
    }
    // эксперимент
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, ksr);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    //************************ сигма
    QVector<double>  gsigma(qmax);

    for(int i=0;i<qmax;i++) //x
    {
        gsigma[i]=sqrt(dispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    ui->widget->xAxis->setRange(-0.1+0, pomax+0.1);
    ui->widget->yAxis->setRange(-0.3+0,m+2);

    ui->widget->replot();
}

void MainWindow::on_pushButton_mr_clicked()
{
    int n = ui->nEdit->text().toInt();
    int m = ui->mEdit->text().toInt();
    int pomax = ui->pomaxEdit->text().toInt();
    int r = ui->rEdit->text().toInt();

    //****************** теория
    double h = 0.01;
    int Q=(pomax-0)/h + 2;
    QVector<double> s(Q), t(Q); //теория
    int qmax=pomax*5+1;
    int dlpo=0;
    int counter=0;
    QVector<double> prmx(Q), prmy(Q);
    int j=0;
    for (double X=0; X<=pomax; X+=h)
    {
        prmx[j] = X;
        prmy[j] = m+1;
        j++;
    }
    for (double x=0; x<=pomax; x+=h)
    {
        s[counter] = x;
        if(dlpo==100)
        {
            t[counter]=(m+1)/(static_cast<double>(2));
        }
        else
            t[counter] = x*(1-(m+2-m*x-x)*pow(x,m+1))/(1-pow(x,m+2))/(1-x);
        counter++;
        dlpo++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(prmx, prmy);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));

    //******************** эксп
    QVector<double> dispe(qmax); //дисперсия для суммы
    QVector<double> ksr(qmax), k, celpo(qmax);  // среднее
    double sumd, po;
    int uu=0;
    //tttttt
    double tau1, tau2;
    bool busy;
    int amountQueue, summApll, amountApll;
    //ttttt
    srand(time(0));
    for(po=0; po <=pomax+0.1; po=po+0.2)
    {
        celpo[uu]=po;
        sumd=0;
        busy = false;  // занятость канала обработки
        amountQueue = 0 ; // количество заявок в очереди
        summApll = 0;  // среднее количество заявок - наше К

        if(po==0)
            ksr[uu]=0;
        else
        {
            tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0)))); // время прихода новой заявки
            tau2 = 0;  // время обработки заявки

            for(double ch = 0; ch < n; ch++)
            {
                amountApll = 0; // счетчик обслуженных заявок
                while(amountApll < 10)
                {
                    if(tau1==0)  // если заявка пришла в систему за время tau1
                    {
                        if(amountQueue==0 && tau2==0){  // если очередь пуста И никого не обрабатывают
                            tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0)))); // задается время прихода новой зявки
                            tau2 = tauerl2(r); // задается время обработки текущей заявки
                            busy = true;
                        }
                        else
                        { //если очередь пуста ИЛИ никого не обрабатывают
                            if (amountQueue < (m+1)){  // если в очереди есть место и кого-то обрабатывают
                                amountQueue += 1;  // помещаем текущую заявку в очередь
                                tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // задаем время прихода новой заявки
                            }
                            else  // если в очереди места нет
                                tau1 = double(-1.0/po)*log(static_cast<double>(s_rand())/(static_cast<double>(RAND_MAX/(1-0))));  // выкидываем заявку в поток отказа и ждем новую заявку
                        }
                    }
                    if (tau2==0) // если чувак обработался
                    {
                        if (amountQueue > 0)
                        {  // если в очереди кто-то есть
                            amountQueue -= 1 ; // заявка из очереди переходит в пункт обработки
                            tau2 = tauerl2(r);  // задаем время обработки этой заявки
                            busy = true;  // пункт обработки занят
                        }
                        else
                            busy = false; // пункт обработки не занят
                    }
                    if (busy==true)  // если в пункте обработки есть заявка
                    {
                        if (tau1 >= tau2)  // если время прихода новой заявки больше чем время обработки текущей заявки
                        {
                            tau1 -= tau2;
                            tau2 -= tau2;
                        }
                        else if (tau2 >= tau1)
                        {
                            tau2 -= tau1;
                            tau1 -= tau1;
                        }
                    }
                    else
                        tau1 = 0;

                    if(tau2==0 && busy==true)
                    {
                        amountApll += 1;
                        if (amountApll == 10)
                        {
                            summApll += amountQueue;
                            break;
                        }
                        busy = false;
                    }

                }
                k.append(amountQueue);
            }
        }

        ksr[uu]=(double(summApll)/double(n));

        for(int j=0;j<k.size();j++)  //дисперсия
        {
            sumd=sumd+(k[j]-ksr[uu])*(k[j]-ksr[uu]);
        }
        dispe[uu]=sumd/(static_cast<double>(k.size()-1));

        k.clear();

        uu++;
    }
    // эксперимент
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, ksr);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    //************************ сигма
    QVector<double>  gsigma(qmax);

    for(int i=0;i<qmax;i++) //x
    {
        gsigma[i]=sqrt(dispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    ui->widget->xAxis->setRange(-0.1+0, pomax+0.1);
    ui->widget->yAxis->setRange(-0.3+0,m+2);

    ui->widget->replot();
}

void MainWindow::on_pushButton_rr_clicked()
{
    int n = ui->nEdit->text().toInt();
    int m = ui->mEdit->text().toInt();
    int pomax = ui->pomaxEdit->text().toInt();
    int r = ui->rEdit->text().toInt();

    //****************** теория
    double h = 0.01;
    int Q=(pomax-0)/h + 2;
    QVector<double> s(Q), t(Q); //теория
    int qmax=pomax*5+1;
    int dlpo=0;
    int counter=0;
    QVector<double> prmx(Q), prmy(Q);
    int j=0;
    for (double X=0; X<=pomax; X+=h)
    {
        prmx[j] = X;
        prmy[j] = m+1;
        j++;
    }
    for (double x=0; x<=pomax; x+=h)
    {
        s[counter] = x;
        if(dlpo==100)
        {
            t[counter]=(m+1)/(static_cast<double>(2));
        }
        else
            t[counter] = x*(1-(m+2-m*x-x)*pow(x,m+1))/(1-pow(x,m+2))/(1-x);
        counter++;
        dlpo++;
    }
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(s, t);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(255,0,0, 255));
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(prmx, prmy);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,255,0, 255));

    //******************** эксп
    QVector<double> dispe(qmax); //дисперсия для суммы
    QVector<double> ksr(qmax), k, celpo(qmax);  // среднее
    double sumd, po;
    int uu=0;
    //tttttt
    double tau1, tau2;
    bool busy;
    int amountQueue, summApll, amountApll;
    //ttttt
    srand(time(0));
    for(po=0; po <=pomax+0.1; po=po+0.2)
    {
        celpo[uu]=po;
        sumd=0;
        busy = false;  // занятость канала обработки
        amountQueue = 0 ; // количество заявок в очереди
        summApll = 0;  // среднее количество заявок - наше К

        if(po==0)
            ksr[uu]=0;
        else
        {
            tau1 = tauerl1(po, r); // время прихода новой заявки
            tau2 = 0;  // время обработки заявки

            for(double ch = 0; ch < n; ch++)
            {
                amountApll = 0; // счетчик обслуженных заявок
                while(amountApll < 10)
                {
                    if(tau1==0)  // если заявка пришла в систему за время tau1
                    {
                        if(amountQueue==0 && tau2==0){  // если очередь пуста И никого не обрабатывают
                            tau1 = tauerl1(po, r); // задается время прихода новой зявки
                            tau2 = tauerl2(r);  // задается время обработки текущей заявки
                            busy = true;
                        }
                        else
                        { //если очередь пуста ИЛИ никого не обрабатывают
                            if (amountQueue < (m+1)){  // если в очереди есть место и кого-то обрабатывают
                                amountQueue += 1;  // помещаем текущую заявку в очередь
                                tau1 = tauerl1(po, r);  // задаем время прихода новой заявки
                            }
                            else  // если в очереди места нет
                                tau1 = tauerl1(po, r);  // выкидываем заявку в поток отказа и ждем новую заявку
                        }
                    }
                    if (tau2==0) // если чувак обработался
                    {
                        if (amountQueue > 0)
                        {  // если в очереди кто-то есть
                            amountQueue -= 1 ; // заявка из очереди переходит в пункт обработки
                            tau2 = tauerl2(r);  // задаем время обработки этой заявки
                            busy = true;  // пункт обработки занят
                        }
                        else
                            busy = false; // пункт обработки не занят
                    }
                    if (busy==true)  // если в пункте обработки есть заявка
                    {
                        if (tau1 >= tau2)  // если время прихода новой заявки больше чем время обработки текущей заявки
                        {
                            tau1 -= tau2;
                            tau2 -= tau2;
                        }
                        else if (tau2 >= tau1)
                        {
                            tau2 -= tau1;
                            tau1 -= tau1;
                        }
                    }
                    else
                        tau1 = 0;

                    if(tau2==0 && busy==true)
                    {
                        amountApll += 1;
                        if (amountApll == 10)
                        {
                            summApll += amountQueue;
                            break;
                        }
                        busy = false;
                    }

                }
                k.append(amountQueue);
            }
        }

        ksr[uu]=(double(summApll)/double(n));

        for(int j=0;j<k.size();j++)  //дисперсия
        {
            sumd=sumd+(k[j]-ksr[uu])*(k[j]-ksr[uu]);
        }
        dispe[uu]=sumd/(static_cast<double>(k.size()-1));

        k.clear();

        uu++;
    }
    // эксперимент
    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, ksr);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,255, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    //************************ сигма
    QVector<double>  gsigma(qmax);

    for(int i=0;i<qmax;i++) //x
    {
        gsigma[i]=sqrt(dispe[i]);
    }

    ui->widget->addGraph();
    ui->widget->graph(ui->widget->graphCount()-1)->setData(celpo, gsigma);
    ui->widget->graph(ui->widget->graphCount()-1)->setPen(QColor(0,0,0, 255));
    ui->widget->graph(ui->widget->graphCount()-1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(ui->widget->graphCount()-1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    ui->widget->xAxis->setRange(-0.1+0, pomax+0.1);
    ui->widget->yAxis->setRange(-0.3+0,m+2);

    ui->widget->replot();
}


