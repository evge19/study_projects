#include <QWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <typeinfo>
#include "moveitem.h"
#include "widget.h"


MoveItem::MoveItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

MoveItem::~MoveItem()
{
}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-30,-50,100,20+amatr*15+ammet*15);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect headerRect(-30, -50, 100, 20);
    QRect atrRect(-30,-30,100,amatr*15);
    QRect metRect(-30,-30+amatr*15,100,ammet*15);
    painter->setPen(Qt::black);
    painter->drawRect(atrRect);
    painter->drawRect(metRect);
    painter->drawRect(headerRect);

    painter->drawText(headerRect, Qt::AlignHCenter | Qt::AlignVCenter, classTitle, &headerRect);
    painter->drawText(atrRect, Qt::AlignHCenter | Qt::AlignVCenter, classAtr, &atrRect);
    painter->drawText(metRect, Qt::AlignHCenter | Qt::AlignVCenter, classMet, &metRect);
    //amatr=1; ammet=1;
//    if(linepos.size()==4)
//    {

//        painter->setPen(Qt::green);

//        painter->drawEllipse(-30, -50, 100, 20);
//        painter->drawLine(linepos[0], linepos[1], linepos[2], linepos[3]);
//        linkpressed=false;
//    }
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    if(linkpressed==false)
        this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    qreal tempX,tempY;
    tempX = this->pos().x();
    tempY = this->pos().y();
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    if(linkpressed==false)
    {

        DialogDel classdell;
        MethodsDescr dialmethods;

        if (checkCoordinates(tempX,tempY) && event->buttons() & Qt::RightButton) // удаление класса со сцены и из вектора
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
            if (classdell.exec() == QDialog::Accepted)
            {
                for(int i=0;i<allclasses.size();i++)
                {
                    if(classTitle==allclasses[i])
                    {
                        allclasses.remove(i);
                        allbriefs.remove(i);
                        file_met.remove(i);
                        file_atr.remove(i);
                        file_met_descr.remove(i);
                        alldescrs.remove(i);

                    }
                }
                this->deleteLater();
            }
         }
         if(event->modifiers() & Qt::ControlModifier &&  event->buttons() & Qt::LeftButton)
         {
             this->setCursor(QCursor(Qt::ArrowCursor));
             methods=classMet.split('\n');
             if(metsc==false)
             {
                 for(int i=0;i<methods.size();i++)
                 {
                     metop.append("");
                 }
             }
             oldmetop=metop;
             dialmethods.addline(methods,metop);
             if (dialmethods.exec() == QDialog::Accepted)
             {
                metsce=dialmethods.formeth();
                metop=dialmethods.fordescr();
                QString vrem;
                for(int i=0;i<metsce.size();i++)
                    if(i!=metsce.size()-1)
                        vrem.append(metsce[i]+"\n");
                    else
                        vrem.append(metsce[i]);
                classMet=vrem;
                metsc=true;
                for(int i=0;i<file_met.size();i++)
                {
                    if(file_met[i]==methods)    // замена, если в диалоге что-то исправили
                    {
                        file_met[i]=metsce;
                    }
                }
                if(file_met_descr.size()!=file_met.size())
                {
                    file_met_descr.append(metop);
                }
                else
                {
                    for(int i=0;i<file_met_descr.size();i++)
                    {
                        if(file_met_descr[i]==oldmetop)    // замена, если в диалоге что-то исправили
                        {
                            file_met_descr[i]=metop;
                        }
                    }
                }
            }
        }
    }
    else
    {
        linepos.append(static_cast<int>(tempX));
        linepos.append(static_cast<int>(tempY));
        nasled.append(this->classTitle);
        if((linepos.size()%4==0) && (LinkItem::ll==true))
        {
            checharrow++;
        }

    }
//    qDebug()<<"file_met99999999999999"<<file_met<<file_met_descr;

    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) // изменение класса на сцене
{

    Dialog dialogclass;
    dialogclass.setname(this->classTitle);
    dialogclass.setbrief(this->classBrief);
    dialogclass.setatr(this->classAtr);
    dialogclass.setmet(this->classMet);
    dialogclass.setdescr(this->classDescr);
    oldclassTitle=classTitle; // для файлов
    oldclassBrief=classBrief;
    oldclassDescr=classDescr;
    oldMet=classMet.split('\n');
    oldAtr=classAtr.split('\n');

    if (dialogclass.exec() == QDialog::Accepted)
    {
        classTitle=dialogclass.forname();
        classBrief=dialogclass.forbrief();
        classAtr=dialogclass.foratr();
        classMet=dialogclass.formet();
        classDescr=dialogclass.fordescr();
        amatr=(classAtr.split('\n')).size();
        ammet=(classMet.split('\n')).size(); //количесвто методов
        bool checkclasses=false;
        bool checkbriefs=false;
        bool checkdescrs=false;
        if(allclasses.size()!=0)
        {
            for(int i=0;i<allclasses.size();i++)
            {
                if(allclasses[i]==oldclassTitle)    // замена, если в диалоге что-то исправили
                {
                    allclasses[i]=classTitle;
                    checkclasses=true;
                }
                if(allbriefs[i]==oldclassBrief)
                {
                    allbriefs[i]=classBrief;
                    checkbriefs=true;
                }
                if(alldescrs[i]==oldclassDescr)
                {
                    alldescrs[i]=classDescr;
                    checkdescrs=true;
                }


            }
            if(checkclasses==false)
                allclasses.append(classTitle);
            if(checkbriefs==false)
                allbriefs.append(classBrief);
            if(checkdescrs==false)
                alldescrs.append(classDescr);
        }
        else
        {
            allclasses.append(classTitle);
            allbriefs.append(classBrief);
            alldescrs.append(classDescr);
        }

        vremet=classMet.split('\n');
        vreatr=classAtr.split('\n');
        if(allclasses.size()!=file_met.size())
        {
            file_met.append(vremet);
            file_atr.append(vreatr);
        }
        else
        {

            for(int i=0;i<file_met.size();i++)
            {
                if(file_met[i]==oldMet)    // замена, если в диалоге что-то исправили
                {
                    file_met[i]=vremet;
                }
            }
            for(int i=0;i<file_atr.size();i++)
            {
                if(file_atr[i]==oldAtr)    // замена, если в диалоге что-то исправили
                {
                    file_atr[i]=vreatr;
                }
            }
        }

    }
    this->setToolTip(this->classBrief);
    qDebug()<<"file_atr"<<file_atr;
    Q_UNUSED(event);


}

bool MoveItem::checkCoordinates(qreal &_x, qreal &_y) // проверка координат для удаления
{
    qreal dx1=_x-30;
    qreal dx2=_x+30;
    qreal dy1=_y-30;
    qreal dy2=_y+30;

    if(( _x>=dx1 && _x<=dx2) && (_y>=dy1 && _y<=dy2)){
        return  true;
       } else {
        return  false;
       }
}
