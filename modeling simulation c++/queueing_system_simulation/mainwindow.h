#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_rm_clicked();

    void on_pushButton_mr_clicked();

    void on_pushButton_rr_clicked();

    double tauerl1(double ro1, int r1);
    double tauerl2(int r1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
