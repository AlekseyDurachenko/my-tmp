#include "mydrawitem.h"

#include <QPainter>

MyDrawItem::MyDrawItem(QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
{
    setFlag(ItemClipsToShape, true);
}

void MyDrawItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    //painter->drawRect(rect());
    painter->drawRect(0, 0, 150, 250);
}

QPainterPath MyDrawItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 100, 100);
    path.addEllipse(QRectF(100, 100, 50, 100));
    return path;
}
