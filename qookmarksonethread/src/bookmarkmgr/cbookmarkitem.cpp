#include "cbookmarkitem.h"
#include "ctagitem.h"
#include "cbookmarkmgr.h"


CBookmarkItem::CBookmarkItem(CBookmarkMgr *mgr)
{
    m_mgr = mgr;
}

CBookmarkItem::CBookmarkItem(const CBookmark &data, CBookmarkMgr *mgr)
{
    m_data = data;
    m_mgr = mgr;
}

CBookmarkItem::~CBookmarkItem()
{
}

int CBookmarkItem::index() const
{
    return m_mgr->bookmarkIndexOf(const_cast<CBookmarkItem *>(this));
}

void CBookmarkItem::setData(const CBookmark &data)
{
    CBookmarkItem *item = mgr()->bookmarkFind(data.url());
    if (item && item != this)
        return;

    if (m_data == data)
        return;

    m_data = data;
    m_mgr->callbackBookmarkDataChanged(this);
}
