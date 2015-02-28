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
#ifndef CBOOKMARKMGR_H
#define CBOOKMARKMGR_H

#include <QObject>
#include "cbookmarkitem.h"
class CMgr;
class CTagMgr;


class CBookmarkMgr : public QObject
{
    Q_OBJECT

    friend class CBookmarkItem;
    friend class CTagMgr;
    friend class CMgr;
private:
    explicit CBookmarkMgr(CMgr *mgr = 0);
    virtual ~CBookmarkMgr();
public:
    inline CMgr *mgr() const;

    inline int count() const;
    int indexOf(CBookmarkItem *item) const;
    int indexOf(const QUrl &url) const;
    inline const QList<CBookmarkItem *> &bookmarks() const;
    inline CBookmarkItem *at(int index) const;
    CBookmarkItem *find(const QUrl &url) const;
    CBookmarkItem *add(const CBookmark &data);
    CBookmarkItem *replace(const CBookmark &data);
    void removeAt(int index);
    void removeAll();
signals:
    void aboutToInserted(int first, int last);
    void inserted(int first, int last);
    void aboutToRemoved(int first, int last);
    void removed(int first, int last);
    void dataChanged(CBookmarkItem *item);
    void tagsChanged(CBookmarkItem *item);
private:
    void callbackDataChanged(CBookmarkItem *item);
    void callbackTagsChanged(CBookmarkItem *item);
private:
    QList<CBookmarkItem *> m_bookmarkItems;
    CMgr *m_mgr;
};

CMgr *CBookmarkMgr::mgr() const
{
    return m_mgr;
}

int CBookmarkMgr::count() const
{
    return m_bookmarkItems.count();
}

const QList<CBookmarkItem *> &CBookmarkMgr::bookmarks() const
{
    return m_bookmarkItems;
}

CBookmarkItem *CBookmarkMgr::at(int index) const
{
    return m_bookmarkItems.at(index);
}


#endif // CBOOKMARKMGR_H
