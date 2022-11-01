#include "dialoglink.h"
#include "ui_dialoglink.h"

DialogLink::DialogLink(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLink)
{
    ui->setupUi(this);
    setWindowTitle("Отношение между классами");
}

DialogLink::~DialogLink()
{
    delete ui;
}

QString DialogLink::getlink()
{
    return ui->comboBox->currentText();
}
