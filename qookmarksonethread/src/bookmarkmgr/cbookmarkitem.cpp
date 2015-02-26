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
    notifyTagsAboutDestroyed();
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

void CBookmarkItem::notifyTagsAboutDestroyed()
{
    foreach (CTagItem *item, m_tags)
        item->callbackBookmarkDestroyed(this);
}

void CBookmarkItem::callbackTagRegistred(CTagItem *tag)
{
    if (m_tags.contains(tag))
        return;

    m_tags.insert(tag);
    mgr()->callbackBookmarkTagsChanged(this);
}

void CBookmarkItem::callbackTagUnregistred(CTagItem *tag)
{
    if (!m_tags.contains(tag))
        return;

    m_tags.remove(tag);
    mgr()->callbackBookmarkTagsChanged(this);
}
