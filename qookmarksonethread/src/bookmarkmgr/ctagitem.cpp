#include "ctagitem.h"
#include "cbookmarkitem.h"
#include "cbookmarkmgr.h"


CTagItem::CTagItem(CBookmarkMgr *mgr, CTagItem *parent)
{
    m_mgr = mgr;
    m_parent = parent;
}

CTagItem::CTagItem(const CTagData &data, CBookmarkMgr *mgr, CTagItem *parent)
{
    m_data = data;
    m_mgr = mgr;
    m_parent = parent;
}

CTagItem::~CTagItem()
{
    while (m_children.count())
        delete m_children.takeLast();

    notifyBookmarksAboutDestroyed();
}

void CTagItem::setData(const CTagData &data)
{
    m_data = data;
    m_mgr->callbackTagDataChanged(m_parent, this);
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

CTagItem *CTagItem::takeChild(int index)
{
    CTagItem *item = m_children.takeAt(index);
    item->setParent(0);
    return item;
}

void CTagItem::notifyBookmarksAboutDestroyed()
{
    foreach (CBookmarkItem *bookmark, m_bookmarks)
        bookmark->callbackTagDestroyed(this);
}

void CTagItem::callbackBookmarkRegistred(CBookmarkItem *bookmark)
{
    m_bookmarks.insert(bookmark);
}

void CTagItem::callbackBookmarkUnregistred(CBookmarkItem *bookmark)
{
    m_bookmarks.remove(bookmark);
}
