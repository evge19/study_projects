#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile(QString fileName)
{

    QFile myPassFile(fileName);

    if(myPassFile.open(QIODevice::WriteOnly  | QIODevice::Text))
    {
        QTextStream writeStream(&myPassFile);

        int rowsSize = passes.size();
        for (int i = 0; i < rowsSize; i++)
        {
            writeStream << passes.front();
            passes.pop_front();
            writeStream <<"\r\n";
        }
        myPassFile.close();

    }
    else
        qDebug() << "Error with writting";
}

int MainWindow::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

QStringList MainWindow::strToVec(QString str, int strPartLen)
{
    QStringList result;
    str.push_front("1");

    for (int i = 1; i < str.size(); ++i)
    {
        if (i % strPartLen == 0)
        {
            result.push_back(str.mid(i - strPartLen + 1, strPartLen));
        }
    }
    if ((str.size() - 1) % strPartLen != 0)
    {
        result.push_back(str.right((str.size() - 1) % strPartLen) + QString((str.size() - 1) % strPartLen, ' '));
    }
    return result;
}

QString MainWindow::toNormRight(QString str, QString order)
{
    QString result;
    result.resize(str.size());

    for(int i = 0; i < order.size(); ++i)
    {
        int pos = QString(order[i]).toInt() - 1;
        result[pos] = str[i];

    }
    return result;
}

void MainWindow::on_giveBtn_clicked()
{
    QString ishStr = ui->ishEdit->text();
//    int len = ishStr.size();
    int size = ui->sEdit->text().toInt();
    QStringList parts = strToVec(ishStr, size);
    QString order = ui->perest->text();
    QString shifStr;
    for (auto & block : parts)
    {
        for(int i = 0; i < order.size(); ++i)
        {
            shifStr.append(block[QString(order[i]).toInt() - 1]);
        }
    }

//   qDebug()<<shifStr;
    ui->shifEdit->setText(shifStr);

}

void MainWindow::on_giveBtn_2_clicked()
{
    QString shifStr = ui->shifEdit_2->text();
    int size = ui->sEdit_2->text().toInt();
    QStringList parts = strToVec(shifStr, size);
//    qDebug()<<parts;
    QString order = ui->perest->text();
    QString ishStr;

    for (auto & block : parts)
    {
       ishStr.append(toNormRight(block, order));
    }


    ui->ishEdit_2->setText(ishStr);

}
