#include <mine.h>

Mine::Mine(QObject *parent):
    QObject(parent), QGraphicsItem()
{

}

QRectF Mine::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}

void Mine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::gray);
    painter->drawRect(5, 5, 10, 10);
}


