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

    foreach (CBookmarkItem *item, m_bookmarks.values())
    {
        m_bookmarks.remove(item);
        mgr()->callbackTagBookmarkRemoved(this, item);
    }
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

QSet<CBookmarkItem *> CTagItem::bookmarks(bool recursive) const
{
    if (!recursive)
        return m_bookmarks;

    QSet<CBookmarkItem *> bookmarks = m_bookmarks;
    foreach (CTagItem *item, m_children)
        bookmarks += item->bookmarks(recursive);

    return bookmarks;
}

void CTagItem::bookmarkAdd(CBookmarkItem *item)
{
    m_bookmarks.insert(item);
    mgr()->callbackTagBookmarkInserted(this, item);
}

void CTagItem::bookmarkRemove(CBookmarkItem *item)
{
    m_bookmarks.remove(item);
    mgr()->callbackTagBookmarkRemoved(this, item);
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
