#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_giveBtn_clicked();

    void on_giveBtn_2_clicked();

private:
    void saveToFile(QString fileName = "Pass.txt");
    int randInt(int low, int high);
    QStringList strToVec(QString str, int strPartLen);
    QString toNormRight(QString str, QString order);
    Ui::MainWindow *ui;
    QStringList passes;
    QString alf = "ABCDEFGHIGKLMNIZXVNMzxcvnmabcdefghigklm";

};

#endif // MAINWINDOW_H
