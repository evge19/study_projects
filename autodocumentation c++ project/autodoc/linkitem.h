#ifndef LINKITEM_H
#define LINKITEM_H
#include <QObject>
#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include "dialog.h"
#include "dialogdel.h"
#include "methodsdescr.h"
#include "moveitem.h"

class LinkItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit LinkItem(QObject *parent = 0);
    static inline bool ll=false;
    static inline int typerelat;
    ~LinkItem();

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:

};

#endif // LINKITEM_H
