#ifndef CTAGITEM_H
#define CTAGITEM_H

#include <QSet>
#include "ctag.h"

class CBookmarkItem;
class CBookmarkMgr;
class CTagItem
{
    friend class CBookmarkMgr;
    friend class CBookmarkItem;

    CTagItem(CBookmarkMgr *mgr, CTagItem *parent = 0);
    CTagItem(const CTag &data, CBookmarkMgr *mgr, CTagItem *parent = 0);
public:
    ~CTagItem();

    inline CBookmarkMgr *mgr() const;
    inline CTagItem *parent() const;
    inline int index() const;

    inline int childCount();
    inline int indexOfChild(CTagItem *item) const;
    inline CTagItem *child(int index) const;
    inline CTagItem *findChild(const QString &name) const;
    inline const QList<CTagItem *> &children() const;

    inline const CTag &data() const;
    void setData(const CTag &data);
private:
    void setParent(CTagItem *parent);
    void addChild(CTagItem *item);
    CTagItem *takeChild(CTagItem *item);
    CTagItem *takeChild(int index);
private:
    void notifyBookmarksAboutDestroyed();
private:
    void callbackBookmarkRegistred(CBookmarkItem *bookmark);
    void callbackBookmarkUnregistred(CBookmarkItem *bookmark);
private:
    CBookmarkMgr *m_mgr;
    CTagItem *m_parent;
    CTag m_data;
    QSet<CBookmarkItem *> m_bookmarks;
    QList<CTagItem *> m_children;
};

CBookmarkMgr *CTagItem::mgr() const
{
    return m_mgr;
}

CTagItem *CTagItem::parent() const
{
    return m_parent;
}

int CTagItem::index() const
{
    return m_parent->indexOfChild(const_cast<CTagItem *>(this));
}

int CTagItem::childCount()
{
    return m_children.count();
}

int CTagItem::indexOfChild(CTagItem *item) const
{
    return m_children.indexOf(item);
}

CTagItem *CTagItem::child(int index) const
{
    return m_children.value(index);
}

CTagItem *CTagItem::findChild(const QString &name) const
{
    foreach (CTagItem *tag, m_children)
        if (tag->data().name() == name)
            return tag;
    return 0;
}

const QList<CTagItem *> &CTagItem::children() const
{
    return m_children;
}

const CTag &CTagItem::data() const
{
    return m_data;
}


#endif // CTAGITEM_H
