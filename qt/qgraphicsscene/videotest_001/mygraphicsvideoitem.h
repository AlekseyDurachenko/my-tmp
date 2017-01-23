#ifndef MYGRAPHICSVIDEOITEM_H
#define MYGRAPHICSVIDEOITEM_H

#include <QGraphicsVideoItem>

class MyGraphicsVideoItem : public QGraphicsVideoItem
{
    Q_OBJECT
public:
    MyGraphicsVideoItem(QGraphicsItem *parent = Q_NULLPTR);

    bool hasShowMask() const;

    void setShowMask(bool show);

    virtual QPainterPath shape() const override final;
private:
    bool m_showMask;
};


#endif // MYGRAPHICSVIDEOITEM_H
