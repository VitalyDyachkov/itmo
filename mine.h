#ifndef MINE_H
#define MINE_H


#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>

class Mine : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Mine(QObject *parent = 0);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // MINE_H
