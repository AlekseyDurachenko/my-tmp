#include "cbookmarkitem.h"
#include "ctagitem.h"
#include "cbookmarkmgr.h"

CBookmarkItem::CBookmarkItem(CBookmarkMgr *mgr)
{
    m_mgr = mgr;
}

CBookmarkItem::CBookmarkItem(const CBookmark &data,
        const QSet<CTagItem *> &tags, CBookmarkMgr *mgr)
{
    m_data = data;
    m_tags = tags;
    m_mgr = mgr;
}

CBookmarkItem::~CBookmarkItem()
{
    foreach (CTagItem *tag, m_tags)
        tag->callbackBookmarkUnregistred(this);
}

int CBookmarkItem::index() const
{
    return m_mgr->bookmarkIndexOf(const_cast<CBookmarkItem *>(this));
}

void CBookmarkItem::setData(const CBookmark &data)
{
    privateSetData(data);
    m_mgr->callbackBookmarkDataChanged(this);
}

void CBookmarkItem::setData(const CBookmark &data,
        const QSet<CTagItem *> &tags)
{
    privateSetData(data);
    privateSetTags(tags);
    m_mgr->callbackBookmarkDataChanged(this);
}

void CBookmarkItem::setTags(const QSet<CTagItem *> &tags)
{
    privateSetTags(tags);
    m_mgr->callbackBookmarkDataChanged(this);
}

void CBookmarkItem::privateSetData(const CBookmark &data)
{
    m_data = data;
}

void CBookmarkItem::privateSetTags(const QSet<CTagItem *> &tags)
{
    QSet<CTagItem *> removing = m_tags - tags;
    QSet<CTagItem *> inserting = tags - m_tags;

    foreach (CTagItem *tag, removing)
        tag->callbackBookmarkUnregistred(this);
    foreach (CTagItem *tag, inserting)
        tag->callbackBookmarkRegistred(this);

    m_tags = tags;
}

void CBookmarkItem::callbackTagDestroyed(CTagItem *tag)
{
    m_tags.remove(tag);
    m_mgr->callbackBookmarkDataChanged(this);
}
