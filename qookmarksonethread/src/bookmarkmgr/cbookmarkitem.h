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

    inline const QSet<CTagItem *> &tags() const;
private:
    void notifyTagsAboutDestroyed();
private:
    void callbackTagRegistred(CTagItem *tag);
    void callbackTagUnregistred(CTagItem *tag);
private:
    CBookmarkMgr *m_mgr;
    QSet<CTagItem *> m_tags;
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

const QSet<CTagItem *> &CBookmarkItem::tags() const
{
    return m_tags;
}


#endif // CBOOKMARKITEM_H
