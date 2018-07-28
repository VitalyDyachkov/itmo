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
   painter->drawRect(5, 5, 20, 20);

}
void Step::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalStep();
    QGraphicsItem::mousePressEvent(event);
}
