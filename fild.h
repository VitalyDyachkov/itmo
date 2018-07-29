#ifndef FILD_H
#define FILD_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include<QPushButton>

class Step : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Step(QObject *parent = 0);
    ~Step();

   // void moving(int x, int y, pconsts::direction cur_dir);

signals:
   // void signalStep(QGraphicsItem *point);
    void signalStep(QGraphicsItem *one_step);
protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // FILD_H
