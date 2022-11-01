#ifndef METHODSDESCR_H
#define METHODSDESCR_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QKeyEvent>
#include "moveitem.h"

namespace Ui {
class MethodsDescr;
}

class MethodsDescr : public QDialog
{
    Q_OBJECT

public:
    explicit MethodsDescr(QWidget *parent = nullptr);
    void addline(QList<QString> metna, QList<QString> metnaop);
    QList<QString> formeth();
    QList<QString> meths;
//    QVector<QLineEdit> vmeths;
    QList<QString> fordescr();
    QList<QString> descr;
    int p;

    ~MethodsDescr();

private:
    Ui::MethodsDescr *ui;
private slots:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // METHODSDESCR_H
