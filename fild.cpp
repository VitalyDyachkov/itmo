#include <fild.h>
#include <QList>
#include <QGraphicsScene>
#include<QPushButton>

Step::Step(QObject *parent):
    QObject(parent), QGraphicsItem()
{

}

Step::~Step()
{

}
QRectF Step::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}


void Step::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   painter->setBrush(Qt::gray);
   painter->drawRect(0, 0, 20, 20);

}
void Step::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QRectF rect(this->x(), this->y(), 20, 20);

     QList<QGraphicsItem *> foundItem = scene()->items(rect);
qDebug() << foundItem;
    foreach (QGraphicsItem *item, foundItem) {
     //   if (item == this)
     //       continue;
        //qDebug() << foundItem;
        //qDebug() << foundItem;
      //  scene()->removeItem(item);
          emit signalStep(item);
    }

    QGraphicsItem::mousePressEvent(event);
}
