#include "ctagitem.h"
#include "cbookmarkitem.h"


CTagItem::CTagItem(CTagItem *parent, CTagMgr *mgr)
{
    m_parent = parent;
    m_mgr = mgr;
}

CTagItem::CTagItem(const CTagData &data, CTagItem *parent, CTagMgr *mgr)
{
    m_data = data;
    m_parent = parent;
    m_mgr = mgr;
}

CTagItem::~CTagItem()
{
    notifyBookmarksAboutDestroyed();
}

void CTagItem::setTagData(const CTagData &data)
{
    m_data = data;
    notifyBookmarksAboutChanges();
}

void CTagItem::notifyBookmarksAboutChanges()
{
    foreach (CBookmarkItem *bookmark, m_bookmarks)
        bookmark->callbackTagChanged(this);
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
