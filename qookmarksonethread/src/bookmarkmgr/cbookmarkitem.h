#ifndef CBOOKMARKITEM_H
#define CBOOKMARKITEM_H

#include "cbookmark.h"
#include "ctagitem.h"


class CBookmarkMgr;
class CBookmarkItem
{
    friend class CBookmarkMgr;
    friend class CTagItem;

    CBookmarkItem(CBookmarkMgr *mgr);
    CBookmarkItem(const CBookmark &data, CBookmarkMgr *mgr);
    ~CBookmarkItem();
public:
    inline CBookmarkMgr *mgr() const;
    int index() const;

    inline const CBookmark &data() const;
    void setData(const CBookmark &data);
private:
    CBookmarkMgr *m_mgr;
    CBookmark m_data;
};

CBookmarkMgr *CBookmarkItem::mgr() const
{
    return m_mgr;
}

const CBookmark &CBookmarkItem::data() const
{
    return m_data;
}


#endif // CBOOKMARKITEM_H
