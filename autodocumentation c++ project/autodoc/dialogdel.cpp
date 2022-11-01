#include "dialogdel.h"
#include "ui_dialogdel.h"

DialogDel::DialogDel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDel)
{
    ui->setupUi(this);
    setWindowTitle("Удаление класса");
}

DialogDel::~DialogDel()
{
    delete ui;
}
