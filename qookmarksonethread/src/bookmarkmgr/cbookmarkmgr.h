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
#include "ctagitem.h"


class CBookmarkMgr : public QObject
{
    Q_OBJECT
    friend class CBookmarkItem;
    friend class CTagItem;
public:
    explicit CBookmarkMgr(QObject *parent = 0);
    virtual ~CBookmarkMgr();

    int bookmarkCount() const;
    int bookmarkIndexOf(CBookmarkItem *item) const; // need??
    int bookmarkIndexOf(const QUrl &url) const;     // need??
    CBookmarkItem *bookmarkAt(int index) const;
    CBookmarkItem *bookmarkFind(const QUrl &url) const;
    CBookmarkItem *bookmarkAdd(const CBookmark &data);
    CBookmarkItem *bookmarkAddOrReplace(const CBookmark &data);
    void bookmarkRemove(CBookmarkItem *item);   // need??
    void bookmarkRemove(const QUrl &url);
    void bookmarkRemoveAt(int index);           // need??
    void bookmarkRemoveAll();

    CTagItem *tagRootItem() const;
signals:
    void bookmarkInserted(CBookmarkItem *item);
    void bookmarkRemoved(CBookmarkItem *item);
    void bookmarkDataChanged(CBookmarkItem *item);
    void bookmarkTagsChanged(CBookmarkItem *item);

    void tagInserted(CTagItem *parent, CTagItem* item);
    void tagRemoved(CTagItem *parent, CTagItem* item);
    void tagMoved(CTagItem *oldParent, CTagItem *newParent, CTagItem *item);
    void tagDataChanged(CTagItem *parent, CTagItem* item);
private:
    void callbackBookmarkDataChanged(CBookmarkItem *item);
    void callbackBookmarkTagsChanged(CBookmarkItem *item);
    void callbackTagInserted(CTagItem *parent, CTagItem *item);
    void callbackTagRemoved(CTagItem *parent, CTagItem *item);
    void callbackTagMoved(CTagItem *oldParent, CTagItem *newParent, CTagItem *item);
    void callbackTagDataChanged(CTagItem *parent, CTagItem *item);
private:
    QList<CBookmarkItem *> m_bookmarkItems;
    CTagItem *m_tagRootItem;
};


#endif // CBOOKMARKMGR_H
