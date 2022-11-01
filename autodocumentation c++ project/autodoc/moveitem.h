#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include "dialog.h"
#include "dialogdel.h"
#include "methodsdescr.h"
#include "linkitem.h"

class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveItem(QObject *parent = 0);
    QString classTitle;
    QString classBrief;
    QString classAtr;
    QString classMet;
    QString classDescr;
    int amatr=1;
    int ammet=1;
    QList<QString> methods;
    QList<QString> metsce;
    QList<QString> metop;
    QList<QString> oldmetop;
    static inline QVector<QString>  nasled;
    static inline QVector<QString> allclasses;
    static inline QVector<QString>  allbriefs;
    static inline QVector<QString>  alldescrs;
    static inline bool linkpressed=false;
    static inline QList<int> linepos;
    QString oldclassTitle="", oldclassBrief="", oldclassDescr="";
    bool checkmeth=false;
    bool metsc=false;
    static inline int checharrow=0;
    static inline QVector<QList<QString>> file_met;
    static inline QVector<QList<QString>> file_atr;
    static inline QVector<QList<QString>> file_met_descr;
    int km;
    QList<QString> oldMet;
    QList<QString> oldAtr;
    QList<QString> vremet;
    QList<QString> vreatr;


    ~MoveItem();

signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    bool checkCoordinates(qreal &_x,qreal &_y);

private slots:

};



#endif // MOVEITEM_H
