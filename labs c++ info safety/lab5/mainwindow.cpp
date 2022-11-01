#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

#include <QFileDialog>
#include <QCryptographicHash>
#include <QByteArray>

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


int MainWindow::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

QByteArray MainWindow::calcHash(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly  | QIODevice::Text);
    const qint64 m_bufferSize = 4*1024;

    QCryptographicHash hash(QCryptographicHash::Sha256);
    file.seek(0);
    while (!file.atEnd())
    {
        QByteArray chunk = file.read(m_bufferSize);
        hash.addData(chunk);
    }
    file.close();
    return hash.result();
}

void MainWindow::on_giveBtn_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Select file");
    QByteArray sum = calcHash(fileName);
    if (fileAndSum.contains(fileName) && fileAndSum[fileName] != sum)
        QMessageBox::information(this, "Notification", fileName + " has been changed" );
    if (fileAndSum.contains(fileName) && fileAndSum[fileName] == sum)
        QMessageBox::information(this, "Notification", fileName + " has NOT been changed" );
    fileAndSum[fileName] = sum;
}







void MainWindow::on_giveBtn_2_clicked()
{


}
