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
#include "cnavigationitemmodel.h"
#include <QMimeData>
#include <QStringList>
#include <QIcon>
#include "ctagmgr.h"
#include "ctagitem.h"
#include "cbookmarkmgr.h"
#include "cbookmarkitem.h"
#include "cmanager.h"
#include <QDebug>


CNavigationItemModel::CNavigationItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_tagMgr = 0;
    initTopLevelItems();
    initTopLevelCounters();
}

CNavigationItemModel::CNavigationItemModel(CTagMgr *tagMgr, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_tagMgr = 0;
    initTopLevelItems();
    initTopLevelCounters();
    setTagMgr(tagMgr);
}

CNavigationItemModel::~CNavigationItemModel()
{
}

void CNavigationItemModel::setTagMgr(CTagMgr *tagMgr)
{
    if (m_tagMgr)
        disconnect(m_tagMgr, 0, this, 0);

    m_tagMgr = tagMgr;
    if (m_tagMgr)
    {
        connect(m_tagMgr, SIGNAL(aboutToBeInserted(CTagItem*,int,int)),
                this, SLOT(tagMgr_aboutToBeInserted(CTagItem*,int,int)));
        connect(m_tagMgr, SIGNAL(inserted(CTagItem*,int,int)),
                this, SLOT(tagMgr_inserted(CTagItem*,int,int)));
        connect(m_tagMgr, SIGNAL(aboutToBeRemoved(CTagItem*,int,int)),
                this, SLOT(tagMgr_aboutToBeRemoved(CTagItem*,int,int)));
        connect(m_tagMgr, SIGNAL(removed(CTagItem*,int,int)),
                this, SLOT(tagMgr_removed(CTagItem*,int,int)));
        connect(m_tagMgr, SIGNAL(aboutToBeMoved(CTagItem*,int,int,CTagItem*,int)),
                this, SLOT(tagMgr_aboutToBeMoved(CTagItem*,int,int,CTagItem*,int)));
        connect(m_tagMgr, SIGNAL(moved(CTagItem*,int,int,CTagItem*,int)),
                this, SLOT(tagMgr_moved(CTagItem*,int,int,CTagItem*,int)));
        connect(m_tagMgr, SIGNAL(dataChanged(CTagItem*)),
                this, SLOT(tagMgr_dataChanged(CTagItem*)));
        connect(m_tagMgr, SIGNAL(bookmarksChanged(CTagItem*)),
                this, SLOT(tagMgr_bookmarksChanged(CTagItem*)));
        connect(m_tagMgr, SIGNAL(destroyed()), this, SLOT(tagMgr_destroyed()));
    }

    recalcTopLevelCounters();
    reset();
}

QVariant CNavigationItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_tagMgr)
        return QVariant();

    if (!index.parent().isValid())
        return topLevelData(index, role);

    CTagItem *item = static_cast<CTagItem *>(index.internalPointer());
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
        if (index.column() == 0)
            return QString("%1 (%2)")
                    .arg(item->data().name())
                    .arg(item->bookmarks().count());

    if (role == Qt::DecorationRole)
        if (index.column() == 0)
            return QIcon(":/icons/bookmark-tag.png");

    if (role == Qt::UserRole)
        return QVariant::fromValue(index.internalPointer());

    return QVariant();
}

Qt::ItemFlags CNavigationItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if (!index.parent().isValid())
        return Qt::ItemIsEnabled
                |Qt::ItemIsSelectable
                |Qt::ItemIsDropEnabled;

    return Qt::ItemIsEnabled
            |Qt::ItemIsSelectable
            |Qt::ItemIsDragEnabled
            |Qt::ItemIsDropEnabled;
}

QStringList CNavigationItemModel::mimeTypes() const
{
    return QStringList() << "application/CTagItemList"
                         << "application/CBookmarkItemList";
}

QMimeData *CNavigationItemModel::mimeData(const QModelIndexList &indexes) const
{
    return 0;
}

bool CNavigationItemModel::dropMimeData(const QMimeData *data,
        Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    return false;
}

QVariant CNavigationItemModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal
            && role == Qt::DisplayRole
            && section == 0)
        return tr("Name");

    return QVariant();
}

QModelIndex CNavigationItemModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || !m_tagMgr)
        return QModelIndex();

    if (!parent.isValid())
    {
        if (m_topLevelItems.at(row) == BookmarksRoot)
            return createIndex(row, column, m_tagMgr->rootItem());
        else
            return createIndex(row, column, 0);
    }

    CTagItem *parentItem = static_cast<CTagItem *>(parent.internalPointer());
    return createIndex(row, column, parentItem->at(row));
}

QModelIndex CNavigationItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid() || !m_tagMgr)
        return QModelIndex();

    if (index.internalPointer() == 0
            || index.internalPointer() == m_tagMgr->rootItem())
        return QModelIndex();

    CTagItem *childItem = static_cast<CTagItem *>(index.internalPointer());
    CTagItem *parentItem = childItem->parent();
    if (parentItem == m_tagMgr->rootItem())
        return createIndex(bookmarksIndex(), 0, parentItem);

    return createIndex(parentItem->index(), 0, parentItem);
}

int CNavigationItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_topLevelItems.count();

    if (parent.column() != 0 || !m_tagMgr)
        return 0;

    CTagItem *parentItem = static_cast<CTagItem *>(parent.internalPointer());
    if (!parentItem)
        return 0;

    return parentItem->count();
}

int CNavigationItemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void CNavigationItemModel::tagMgr_aboutToBeInserted(CTagItem *parent,
        int first, int last)
{
    if (parent == m_tagMgr->rootItem())
        beginInsertRows(createIndex(bookmarksIndex(), 0, parent), first, last);
    else
        beginInsertRows(createIndex(parent->index(), 0, parent), first, last);
}

void CNavigationItemModel::tagMgr_inserted(CTagItem *parent,
        int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    endInsertRows();    
}

void CNavigationItemModel::tagMgr_aboutToBeRemoved(CTagItem *parent,
        int first, int last)
{
    if (parent == m_tagMgr->rootItem())
        beginRemoveRows(createIndex(bookmarksIndex(), 0, parent), first, last);
    else
        beginRemoveRows(createIndex(parent->index(), 0, parent), first, last);
}

void CNavigationItemModel::tagMgr_removed(CTagItem *parent,
        int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);

    endRemoveRows();
}

void CNavigationItemModel::tagMgr_aboutToBeMoved(CTagItem *srcParent,
        int srcFirst, int srcLast, CTagItem *dstParent, int dstIndex)
{
    QModelIndex si = createIndex(bookmarksIndex(), 0, m_tagMgr->rootItem());
    QModelIndex di = createIndex(bookmarksIndex(), 0, m_tagMgr->rootItem());
    if (srcParent != m_tagMgr->rootItem())
        si = createIndex(srcParent->index(), 0, srcParent);
    if (dstParent != m_tagMgr->rootItem())
        di = createIndex(dstParent->index(), 0, dstParent);
    beginMoveRows(si, srcFirst, srcLast, di, dstIndex);
}

void CNavigationItemModel::tagMgr_moved(CTagItem *srcParent, int srcFirst,
        int srcLast, CTagItem *dstParent, int dstIndex)
{
    Q_UNUSED(srcParent);
    Q_UNUSED(srcFirst);
    Q_UNUSED(srcLast);
    Q_UNUSED(dstParent);
    Q_UNUSED(dstIndex);

    endMoveRows();
}

void CNavigationItemModel::tagMgr_dataChanged(CTagItem *item)
{
    if (item->isRoot())
    {
        int index = bookmarksIndex();
        emit dataChanged(createIndex(index, 0, item),
                         createIndex(index,  columnCount()-1, item));
    }
    else
    {
        int index = item->index();
        emit dataChanged(createIndex(index, 0, item),
                         createIndex(index,  columnCount()-1, item));
    }
}

void CNavigationItemModel::tagMgr_bookmarksChanged(CTagItem *item)
{
    tagMgr_dataChanged(item);
}

void CNavigationItemModel::tagMgr_destroyed()
{
    m_tagMgr = 0;
}

void CNavigationItemModel::initTopLevelItems()
{
    m_topLevelItems
            << Favorites
            << Rated
            << ReadLater
            << BookmarksRoot
            << Trash;
}

void CNavigationItemModel::initTopLevelCounters()
{
    m_topLevelCounter[Favorites] = 0;
    m_topLevelCounter[Rated] = 0;
    m_topLevelCounter[ReadLater] = 0;
    m_topLevelCounter[BookmarksRoot] = 0;
    m_topLevelCounter[Trash] = 0;
}

int CNavigationItemModel::bookmarksIndex() const
{
    return m_topLevelItems.indexOf(BookmarksRoot);
}

QVariant CNavigationItemModel::topLevelData(const QModelIndex &index,
        int role) const
{
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
        if (index.column() == 0)
            return topLevelName(m_topLevelItems.at(index.row()));

    if (role == Qt::DecorationRole)
        if (index.column() == 0)
            return topLevelIcon(m_topLevelItems.at(index.row()));

    return QVariant();
}

QString CNavigationItemModel::topLevelName(CNavigationItemModel::TopLevelItem item) const
{
    switch (item)
    {
    case Favorites:
        return tr("Favorites (%1)").arg(m_topLevelCounter[Favorites]);
    case Rated:
        return tr("Rated Bookmarks (%1)").arg(m_topLevelCounter[Rated]);
    case ReadLater:
        return tr("Read it Later (%1)").arg(m_topLevelCounter[ReadLater]);
    case BookmarksRoot:
        return tr("Bookmarks (%1)").arg(m_topLevelCounter[BookmarksRoot]);
    case Trash:
        return tr("Trash (%1)").arg(m_topLevelCounter[Trash]);
    }

    return QString();
}

QIcon CNavigationItemModel::topLevelIcon(CNavigationItemModel::TopLevelItem item) const
{
    switch (item)
    {
    case Favorites:
        return QIcon(":/icons/bookmark-favorites.png");
    case Rated:
        return QIcon(":/icons/bookmark-rated.png");
    case ReadLater:
        return QIcon(":/icons/bookmark-readlater.png");
    case BookmarksRoot:
        return QIcon(":/icons/bookmark-bookmarks.png");
    case Trash:
        return QIcon(":/icons/bookmark-trash.png");
    }

    return QIcon();
}

void CNavigationItemModel::recalcTopLevelCounters()
{
    initTopLevelCounters();
    foreach (CBookmarkItem *item, m_tagMgr->mgr()->bookmarkMgr()->bookmarks())
    {
        if (item->data().isTrash())
        {
            m_topLevelCounter[Trash] += 1;
            continue;
        }

        if (item->data().isFavorite())
            m_topLevelCounter[Favorites] = 1;
        if (item->data().rating())
            m_topLevelCounter[Rated] += 1;
        if (item->data().isReadLater())
            m_topLevelCounter[ReadLater] += 1;
        if (item->tags().isEmpty())
            m_topLevelCounter[BookmarksRoot] += 1;
    }
}
