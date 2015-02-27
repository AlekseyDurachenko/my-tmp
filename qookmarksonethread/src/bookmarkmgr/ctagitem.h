// Copyright 2014-2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    ~CTagItem();
public:
    inline CBookmarkMgr *mgr() const;
    inline CTagItem *parent() const;
    inline int index() const;

    inline int childCount();
    inline int indexOfChild(CTagItem *item) const;
    inline CTagItem *child(int index) const;
    inline CTagItem *findChild(const QString &name) const;
    CTagItem *findChild(const QStringList &path) const;
    inline const QList<CTagItem *> &children() const;
    CTagItem *addChild(const CTag &data);
    QStringList path() const;
    bool contains(CTagItem *item) const;
    void moveTo(CTagItem *newParent);
    void remove(CTagItem *item);
    void removeAll();

    inline const QSet<CBookmarkItem *> &bookmarks() const;
    QSet<CBookmarkItem *> bookmarks(bool recursive) const;
    void bookmarkAdd(CBookmarkItem *item);
    void bookmarkRemove(CBookmarkItem *item);

    inline const CTag &data() const;
    void setData(const CTag &data);
private:
    void setParent(CTagItem *parent);
    void addChild(CTagItem *item);
    CTagItem *takeChild(CTagItem *item);
private:
    void callbackBookmarkDestroyed(CBookmarkItem *bookmark);
private:
    CBookmarkMgr *m_mgr;
    CTagItem *m_parent;
    QList<CTagItem *> m_children;
    QSet<CBookmarkItem *> m_bookmarks;
    CTag m_data;
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
    if (m_parent)
        return m_parent->indexOfChild(const_cast<CTagItem *>(this));

    return 0;
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

const QSet<CBookmarkItem *> &CTagItem::bookmarks() const
{
    return m_bookmarks;
}

const CTag &CTagItem::data() const
{
    return m_data;
}


#endif // CTAGITEM_H
