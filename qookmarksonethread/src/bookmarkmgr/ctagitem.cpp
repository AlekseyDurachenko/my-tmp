#include "ctagitem.h"
#include "cbookmarkitem.h"
#include "cbookmarkmgr.h"


CTagItem::CTagItem(CBookmarkMgr *mgr, CTagItem *parent)
{
    m_mgr = mgr;
    m_parent = parent;
}

CTagItem::CTagItem(const CTag &data, CBookmarkMgr *mgr, CTagItem *parent)
{
    m_data = data;
    m_mgr = mgr;
    m_parent = parent;
}

CTagItem::~CTagItem()
{
    while (m_children.count())
        delete m_children.takeLast();
}

void CTagItem::addChild(const CTag &data)
{
    CTagItem *item = new CTagItem(data, mgr(), this);
    m_children.push_back(item);
    mgr()->callbackTagInserted(this, item);
}

void CTagItem::moveTo(CTagItem *newParent)
{
    CTagItem *oldParent = parent();
    CTagItem *item = oldParent->takeChild(this);
    newParent->addChild(item);
    mgr()->callbackTagMoved(oldParent, newParent, item);
}

void CTagItem::remove(CTagItem *item)
{
    item->removeAll();
    m_children.removeAll(item);
    mgr()->callbackTagRemoved(this, item);
    delete item;
}

void CTagItem::removeAll()
{
    while (m_children.count())
    {
        m_children.last()->removeAll();
        CTagItem *item = m_children.takeLast();
        mgr()->callbackTagRemoved(this, item);
        delete item;
    }
}

void CTagItem::setData(const CTag &data)
{
    m_data = data;
    mgr()->callbackTagDataChanged(parent(), this);
}

void CTagItem::setParent(CTagItem *parent)
{
    m_parent = parent;
}

void CTagItem::addChild(CTagItem *item)
{
    item->setParent(this);
    m_children.push_back(item);
}

CTagItem *CTagItem::takeChild(CTagItem *item)
{
    m_children.removeAll(item);
    item->setParent(0);
    return item;
}
