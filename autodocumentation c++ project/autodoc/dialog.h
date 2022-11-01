#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "moveitem.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    Ui::Dialog *ui;\
    QString forname() const;
    QString forbrief() const;
    QString foratr() const;
    QString formet() const;
    QString fordescr() const;
    void setname(QString vvv) const;
    void setbrief(QString bbb) const;
    void setatr(QString qqq) const;
    void setmet(QString ttt) const;
    void setdescr(QString rrr) const;
    ~Dialog();

private slots:
    void on_buttonBox_accepted();


private:

};

#endif // DIALOG_H
