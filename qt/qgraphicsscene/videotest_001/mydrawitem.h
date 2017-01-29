#ifndef MYDRAWITEM_H
#define MYDRAWITEM_H


#include <QGraphicsRectItem>


class MyDrawItem : public QGraphicsRectItem
{
public:
    MyDrawItem(QGraphicsItem *parent = 0);
    virtual void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 ) override final;
    QPainterPath shape() const;
};


#endif // MYDRAWITEM_H
