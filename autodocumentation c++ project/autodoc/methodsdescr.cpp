#include "methodsdescr.h"
#include "ui_methodsdescr.h"

MethodsDescr::MethodsDescr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MethodsDescr)
{
    ui->setupUi(this);
    setWindowTitle("Детализация класса");
    QTextEdit *liedit=new QTextEdit(this);
    liedit->setGeometry(60,10,260,30);
    QLabel *labelm=new QLabel(this);
    labelm->setGeometry(20,44,100,15);
    labelm->setText("Методы класса");


}

void MethodsDescr::addline(QList<QString> metna, QList<QString> metnaop)
{
    p=metna.size();
    for(int i=0;i<metna.size();i++)
    {
        QLineEdit *lied=new QLineEdit(this);
        QTextEdit *teed=new QTextEdit(this);
        lied->setObjectName("lineeds"+static_cast<QString>(i));
        teed->setObjectName("texteds"+static_cast<QString>(i));
        lied->setGeometry(60,60+i*80,260,15);
        teed->setGeometry(60,80+i*80,260,40);
    //    vmeths.append(*lied);
    //    qDebug()<<vmeths[0].text();
        lied->setText(metna[i]);
        teed->setText(metnaop[i]);
    }

    resize(380,200+metna.size()*80);
    ui->buttonBox->setGeometry(200,150+metna.size()*80,161,32);
}

/*!
 * \brief MethodsDescr::formeth
 * \return
 */
QList<QString> MethodsDescr::formeth()
{
    for(int i=0;i<p;i++)
    {
        QLineEdit *le = findChild<QLineEdit*>(QString("lineeds"+static_cast<QString>(i)).arg(i));
        if(le)
        {
            meths.append(le->text());
        }
    }

    return meths;
}
/*!
 * \brief MethodsDescr::fordescr
 * \return
 */
QList<QString> MethodsDescr::fordescr()
{
    for(int i=0;i<p;i++)
    {
        QTextEdit *te = findChild<QTextEdit*>(QString("texteds"+static_cast<QString>(i)).arg(i));
        if(te)
        {
            descr.append(te->toPlainText());
        }
    }
    return descr;
}

MethodsDescr::~MethodsDescr()
{
    delete ui;
}

void MethodsDescr::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
        if (key==Qt::Key_Enter)
        {

        }
}
