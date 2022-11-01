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


    int randInt(int low, int high);
    QByteArray calcHash(QString fileName);
    QHash<QString, QByteArray> fileAndSum;
    Ui::MainWindow *ui;
    QStringList passes;
    QString alf = "ABCDEFGHIGKLMNIZXVNMzxcvnmabcdefghigklm";

};

#endif // MAINWINDOW_H
