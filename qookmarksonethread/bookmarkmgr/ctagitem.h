#ifndef CTAGITEM_H
#define CTAGITEM_H

#include <QSet>
#include "ctagdata.h"

class CTagMgr;
class CBookmarkItem;
class CTagItem
{
    friend class CTagMgr;
    friend class CBookmarkItem;

    CTagItem(CTagItem *parent, CTagMgr *mgr);
    CTagItem(const CTagData &data, CTagItem *parent, CTagMgr *mgr);
public:
    ~CTagItem();

    inline const CTagData &data() const;
    void setTagData(const CTagData &data);
private:
    void notifyBookmarksAboutChanges();
    void notifyBookmarksAboutDestroyed();
private:
    void callbackBookmarkRegistred(CBookmarkItem *bookmark);
    void callbackBookmarkUnregistred(CBookmarkItem *bookmark);
private:
    CTagMgr *m_mgr;
    CTagItem *m_parent;
    CTagData m_data;
    QSet<CBookmarkItem *> m_bookmarks;
};

const CTagData &CTagItem::data() const
{
    return m_data;
}


#endif // CTAGITEM_H
