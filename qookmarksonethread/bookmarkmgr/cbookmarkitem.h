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
    CBookmarkItem(const CBookmark &data, const QSet<CTagItem *> &tags, CBookmarkMgr *mgr);
public:
    ~CBookmarkItem();

    inline const CBookmark &data() const;
    inline const QSet<CTagItem *> &tags() const;
    void setData(const CBookmark &data);
    void setDataTags(const CBookmark &data, const QSet<CTagItem *> &tags);
    void setTags(const QSet<CTagItem *> &tags);
private:
    void privateSetData(const CBookmark &data);
    void privateSetTags(const QSet<CTagItem *> &tags);
private:
    void callbackTagChanged(CTagItem *tag);
    void callbackTagDestroyed(CTagItem *tag);
private:
    CBookmarkMgr *m_mgr;
    QSet<CTagItem *> m_tags;
    CBookmark m_data;
};

const CBookmark &CBookmarkItem::data() const
{
    return m_data;
}

const QSet<CTagItem *> &CBookmarkItem::tags() const
{
    return m_tags;
}


#endif // CBOOKMARKITEM_H
