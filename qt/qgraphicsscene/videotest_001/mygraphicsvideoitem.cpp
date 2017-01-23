#include "mygraphicsvideoitem.h"
#include <QDebug>

MyGraphicsVideoItem::MyGraphicsVideoItem(QGraphicsItem *parent)
    : QGraphicsVideoItem(parent)
{
    m_showMask = false;
}

bool MyGraphicsVideoItem::hasShowMask() const
{
    return m_showMask;
}

void MyGraphicsVideoItem::setShowMask(bool show)
{
    m_showMask = show;
    setFlag(ItemClipsToShape, m_showMask);
}

QPainterPath MyGraphicsVideoItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 100, 100);
    path.addEllipse(QRectF(100, 100, 100, 100));
    return path;
}
