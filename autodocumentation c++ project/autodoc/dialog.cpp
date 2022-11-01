#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Информация о классе");

}

QString Dialog::forname() const
{
    return ui->lineEdit->text();
}

QString Dialog::forbrief() const
{
    return ui->lineEdit_2->text();
}

QString Dialog::foratr() const
{
//    qDebug()<<ui->textEdit_3->toPlainText();
//    QStringList strList=ui->textEdit_3->toPlainText().split('\n');
//    MoveItem::amatr=strList.size();
    return ui->textEdit_3->toPlainText();


}

QString Dialog::formet() const
{
//    QStringList strList=ui->textEdit_3->toPlainText().split('\n');
//    MoveItem::ammet=strList.size();
    return ui->textEdit_2->toPlainText();
}

QString Dialog::fordescr() const
{
    return ui->textEdit->toPlainText();
}

void Dialog::setname(QString vvv) const
{
    if(vvv.isNull()==false)
        ui->lineEdit->setText(vvv);
    else
        ui->lineEdit->setText("");
}

void Dialog::setbrief(QString bbb) const
{
    if(bbb.isNull()==false)
        ui->lineEdit_2->setText(bbb);
    else
        ui->lineEdit_2->setText("");
}

void Dialog::setatr(QString qqq) const
{
    if(qqq.isNull()==false)
        ui->textEdit_3->setText(qqq);
    else
        ui->textEdit_3->setText("");
}

void Dialog::setmet(QString ttt) const
{
    if(ttt.isNull()==false)
        ui->textEdit_2->setText(ttt);
    else
        ui->textEdit_2->setText("");
}

void Dialog::setdescr(QString rrr) const
{
    if(rrr.isNull()==false)
        ui->textEdit->setText(rrr);
    else
        ui->textEdit->setText("");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{


}

