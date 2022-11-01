#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <moveitem.h>
#include <QKeyEvent>
#include "dialog.h"
#include "dialoglink.h"

namespace Ui {
class Widget;
}

class QLineEdit;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    static inline QString dirpr;
    QList<QString> razdel;
    bool checkrelat=false;
    QList<QString> razdelatr;

    ~Widget();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();


    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
};

#endif // WIDGET_H
