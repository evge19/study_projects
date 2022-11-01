#include "linkitem.h"


LinkItem::LinkItem(QObject *parent) :
    QObject(parent), QGraphicsItem()
{

}

LinkItem::~LinkItem()
{
}

QRectF LinkItem::boundingRect() const
{
    return QRectF (MoveItem::linepos[2+MoveItem::checharrow*4]+70, MoveItem::linepos[3+MoveItem::checharrow*4]-25, MoveItem::linepos[0+MoveItem::checharrow*4]-MoveItem::linepos[2+MoveItem::checharrow*4]+20, MoveItem::linepos[1+MoveItem::checharrow*4]-MoveItem::linepos[3+MoveItem::checharrow*4]+20);
}

void LinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRect arrowRect(MoveItem::linepos[0+MoveItem::checharrow*4], MoveItem::linepos[1+MoveItem::checharrow*4], MoveItem::linepos[2+MoveItem::checharrow*4], MoveItem::linepos[3+MoveItem::checharrow*4]);
//    QRect arrowRect(MoveItem::linepos[0+checharrow*4], MoveItem::linepos[1+checharrow*4], MoveItem::linepos[2+checharrow*4], MoveItem::linepos[3+checharrow*4]);
    painter->setPen(Qt::black);
//    painter->drawRect(arrowRect);
    //qDebug()<<MoveItem::linepos[0]<<MoveItem::linepos[1]<<MoveItem::linepos[2]<<MoveItem::linepos[3];



    QPolygon polygon;
//    if(typerelat==1)
    polygon << QPoint(MoveItem::linepos[2+MoveItem::checharrow*4]+70, MoveItem::linepos[3+MoveItem::checharrow*4]-25) << QPoint(MoveItem::linepos[0+MoveItem::checharrow*4]-14-30, MoveItem::linepos[1+MoveItem::checharrow*4]-25) << QPoint(MoveItem::linepos[0+MoveItem::checharrow*4]-14-30, MoveItem::linepos[1+MoveItem::checharrow*4]+7-25) << QPoint(MoveItem::linepos[0+MoveItem::checharrow*4]-30, MoveItem::linepos[1+MoveItem::checharrow*4]-25) << QPoint(MoveItem::linepos[0+MoveItem::checharrow*4]-14-30, MoveItem::linepos[1+MoveItem::checharrow*4]-7-25) << QPoint(MoveItem::linepos[0+MoveItem::checharrow*4]-14-30, MoveItem::linepos[1+MoveItem::checharrow*4]-25);

    //painter->drawLine(MoveItem::linepos[0+MoveItem::checharrow*4], MoveItem::linepos[1+MoveItem::checharrow*4], MoveItem::linepos[2+MoveItem::checharrow*4]-14, MoveItem::linepos[3+MoveItem::checharrow*4]);
    painter->drawPolygon(polygon);

    ll=true;
    Q_UNUSED(option);
    Q_UNUSED(widget);

}



