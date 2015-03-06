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
#include "ctagmgr.h"
#include "ctagitem.h"
#include <QMimeData>
#include <QStringList>
#include <QIcon>
#include <QDebug>


CNavigationItemModel::CNavigationItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_tagMgr = 0;
    initFirstLevelItems();
}

CNavigationItemModel::CNavigationItemModel(CTagMgr *tagMgr, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_tagMgr = 0;
    initFirstLevelItems();
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
    //    QMimeData *mimeData = new QMimeData();

    //    QByteArray encodedData;
    //    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    //    foreach (QModelIndex index, indexes)
    //        if (index.isValid() && index.column() == 0)
    //            stream << static_cast<CTagItem *>(index.internalPointer())->path();

    //    mimeData->setData("application/CTagItemList", encodedData);
    //    return mimeData;
    return 0;
}


bool CNavigationItemModel::dropMimeData(const QMimeData *data,
        Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    //    if (action == Qt::IgnoreAction)
    //        return true;

    //    // new parent for the items
    //    CTagItem *newParent = static_cast<CTagItem *>(parent.internalPointer());
    //    if (!newParent)
    //        return false;

    //    if (data->hasFormat("application/CTagItemList"))
    //    {
    //        // extrct paths
    //        QByteArray encodedData = data->data("application/CTagItemList");
    //        QDataStream stream(&encodedData, QIODevice::ReadOnly);
    //        QList<QStringList> pathList;
    //        int rows = 0;
    //        while (!stream.atEnd())
    //        {
    //            QStringList path;
    //            stream >> path;
    //            pathList << path;
    //            ++rows;
    //        }

    //        // can we move the items?
    //        CBookmarkMgr *mgr = m_rootItem->mgr();
    //        foreach (const QStringList &path, pathList)
    //            //if (!mgr->tagCanMove(newParent, mgr->tagFind(path)))
    //            if (mgr->tagRootItem()->findChild(path)->contains(newParent))
    //                return false;

    //        // move items
    //        foreach (const QStringList &path, pathList)
    //            //mgr->tagMove(newParent, mgr->tagFind(path));
    //            mgr->tagRootItem()->findChild(path)->moveTo(newParent);

    //        return true;
    //    }
    //    else if (data->hasFormat("application/CBookmarkItemList"))
    //    {
    //        // extrct paths
    //        QByteArray encodedData = data->data("application/CBookmarkItemList");
    //        QDataStream stream(&encodedData, QIODevice::ReadOnly);
    //        QList<QUrl> urlList;
    //        int rows = 0;
    //        while (!stream.atEnd())
    //        {
    //            QUrl url;
    //            stream >> url;
    //            urlList << url;
    //            ++rows;
    //        }

    //        // can we move the items?
    //        CBookmarkMgr *mgr = m_rootItem->mgr();
    //        foreach (const QUrl &url, urlList)
    //            //mgr->bookmarkFind(url)->tagAdd(newParent);
    //            newParent->bookmarkAdd(mgr->bookmarkFind(url));

    //        return true;
    //    }

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
        if (m_topLevelItems.at(row) == BookmarkRoot)
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

    return createIndex(parentItem->index(), 0, parentItem);
}


int CNavigationItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0 || !m_tagMgr)
        return 0;

    if (!parent.isValid())
        return m_topLevelItems.count();

    CTagItem *parentItem = static_cast<CTagItem *>(parent.internalPointer());
    if (parentItem == 0)
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
}


void CNavigationItemModel::tagMgr_inserted(CTagItem *parent,
        int first, int last)
{
    if (parent == m_tagMgr->rootItem())
        beginInsertRows(createIndex(m_topLevelItems.indexOf(BookmarkRoot), 0, parent), first, last);
    else
        beginInsertRows(createIndex(parent->index(), 0, parent), first, last);
    endInsertRows();
}


void CNavigationItemModel::tagMgr_aboutToBeRemoved(CTagItem *parent,
        int first, int last)
{
}


void CNavigationItemModel::tagMgr_removed(CTagItem *parent,
        int first, int last)
{
}


void CNavigationItemModel::tagMgr_aboutToBeMoved(CTagItem *srcParent,
        int srcFirst, int srcLast, CTagItem *dstParent, int dstIndex)
{
}


void CNavigationItemModel::tagMgr_moved(CTagItem *srcParent, int srcFirst,
        int srcLast, CTagItem *dstParent, int dstIndex)
{
}


void CNavigationItemModel::tagMgr_dataChanged(CTagItem *item)
{
    if (item->parent())
    {
        int index = item->index();
        emit dataChanged(createIndex(index, 0, item),
                         createIndex(index,  columnCount()-1, item));
    }
    else
    {
        int index = m_topLevelItems.indexOf(BookmarkRoot);
        emit dataChanged(createIndex(index, 0, item),
                         createIndex(index,  columnCount()-1, item));
    }
}


void CNavigationItemModel::tagMgr_bookmarksChanged(CTagItem *item)
{
}

//void CNavigationItemModel::bookmarkmgr_tagInserted(CTagItem *parent, int index)
//{
//    if (parent == m_rootItem)
//        beginInsertRows(QModelIndex(), index, index);
//    else
//        beginInsertRows(createIndex(parent->index(), 0, parent), index, index);
//    endInsertRows();
//}

//void CNavigationItemModel::bookmarkmgr_tagRemoved(CTagItem *parent, int index)
//{
//    if (parent == m_rootItem)
//        beginRemoveRows(QModelIndex(), index, index);
//    else
//        beginRemoveRows(createIndex(parent->index(), 0, parent), index, index);
//    endRemoveRows();
//}

//void CNavigationItemModel::bookmarkmgr_tagMoved(CTagItem *oldParent,
//        int oldIndex, CTagItem *newParent, int newIndex)
//{
//    QModelIndex ox;
//    QModelIndex nx;
//    if (oldParent != m_rootItem)
//        ox = createIndex(oldParent->index(), 0, oldParent);
//    if (newParent != m_rootItem)
//        nx = createIndex(newParent->index(), 0, newParent);

//    beginMoveRows(ox, oldIndex, oldIndex, nx, newIndex);
//    endMoveRows();


//}


void CNavigationItemModel::tagMgr_destroyed()
{
    m_tagMgr = 0;
}

void CNavigationItemModel::initFirstLevelItems()
{
    m_topLevelItems
            << Favorite
            << Rated
            << ReadLater
            << BookmarkRoot
            << Trash;
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
    case Favorite:
        return tr("Favorites");
    case Rated:
        return tr("Rated Bookmarks");
    case ReadLater:
        return tr("Read it Later");
    case BookmarkRoot:
        return tr("Bookmarks");
    case Trash:
        return tr("Trash");
    }

    return QString();
}

QIcon CNavigationItemModel::topLevelIcon(CNavigationItemModel::TopLevelItem item) const
{
    switch (item)
    {
    case Favorite:
        return QIcon(":/icons/bookmark-favorites.png");
    case Rated:
        return QIcon(":/icons/bookmark-rated.png");
    case ReadLater:
        return QIcon(":/icons/bookmark-readlater.png");
    case BookmarkRoot:
        return QIcon(":/icons/bookmark-bookmarks.png");
    case Trash:
        return QIcon(":/icons/bookmark-trash.png");
    }

    return QIcon();
}




//CNavigationItemModel::CNavigationItemModel(QObject *parent) :
//    QAbstractItemModel(parent)
//{
//    m_rootItem = 0;
//    setRootItem(0);
//}

//CNavigationItemModel::CNavigationItemModel(CTagItem *rootItem, QObject *parent) :
//    QAbstractItemModel(parent)
//{
//    m_rootItem = 0;
//    setRootItem(rootItem);
//}

//void CNavigationItemModel::setRootItem(CTagItem *rootItem)
//{
//    beginResetModel();

//    if (m_rootItem)
//        disconnect(m_rootItem->mgr(), 0, this, 0);

//    m_rootItem = rootItem;
//    if (m_rootItem)
//    {
//        connect(m_rootItem->mgr(), SIGNAL(tagInserted(CTagItem *,int)),
//                this, SLOT(bookmarkmgr_tagInserted(CTagItem *,int)));
//        connect(m_rootItem->mgr(), SIGNAL(tagRemoved(CTagItem *,int)),
//                this, SLOT(bookmarkmgr_tagRemoved(CTagItem *,int)));
//        connect(m_rootItem->mgr(), SIGNAL(tagMoved(CTagItem *,int,CTagItem *,int)),
//                this, SLOT(bookmarkmgr_tagMoved(CTagItem *,int,CTagItem *,int)));
//        connect(m_rootItem->mgr(), SIGNAL(tagDataChanged(CTagItem *,int)),
//                this, SLOT(bookmarkmgr_tagDataChanged(CTagItem *,int)));
//        connect(m_rootItem->mgr(), SIGNAL(destroyed()),
//                this, SLOT(bookmarkmgr_destroyed()));
//    }

//    endResetModel();
//}

//QVariant CNavigationItemModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid() || !m_rootItem)
//        return QVariant();

//    CTagItem *item = static_cast<CTagItem *>(index.internalPointer());
//    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
//        if (index.column() == 0)
//            return item->data().name();

////    if (role == Qt::DecorationRole)
////        if (index.column() == 0)
////            return item->icon();

//    if (role == Qt::UserRole)
//        return QVariant::fromValue(index.internalPointer());

//    return QVariant();
//}

//Qt::ItemFlags CNavigationItemModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return 0;

//    //CTagItem *item = static_cast<CTagItem *>(index.internalPointer());
//    //if (item->type() == CTagItem::Tag)
//        return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled;
//    //else
//    //    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDropEnabled;
//}

//QStringList CNavigationItemModel::mimeTypes() const
//{
//    return QStringList() << "application/CTagItemList"
//                         << "application/CBookmarkItemList";
//}

//QMimeData *CNavigationItemModel::mimeData(const QModelIndexList &indexes) const
//{
//    QMimeData *mimeData = new QMimeData();

//    QByteArray encodedData;
//    QDataStream stream(&encodedData, QIODevice::WriteOnly);

//    foreach (QModelIndex index, indexes)
//        if (index.isValid() && index.column() == 0)
//            stream << static_cast<CTagItem *>(index.internalPointer())->path();

//    mimeData->setData("application/CTagItemList", encodedData);
//    return mimeData;
//}

//bool CNavigationItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
//        int /*row*/, int /*column*/, const QModelIndex &parent)
//{
//    if (action == Qt::IgnoreAction)
//        return true;

//    // new parent for the items
//    CTagItem *newParent = static_cast<CTagItem *>(parent.internalPointer());
//    if (!newParent)
//        return false;

//    if (data->hasFormat("application/CTagItemList"))
//    {
//        // extrct paths
//        QByteArray encodedData = data->data("application/CTagItemList");
//        QDataStream stream(&encodedData, QIODevice::ReadOnly);
//        QList<QStringList> pathList;
//        int rows = 0;
//        while (!stream.atEnd())
//        {
//            QStringList path;
//            stream >> path;
//            pathList << path;
//            ++rows;
//        }

//        // can we move the items?
//        CBookmarkMgr *mgr = m_rootItem->mgr();
//        foreach (const QStringList &path, pathList)
//            //if (!mgr->tagCanMove(newParent, mgr->tagFind(path)))
//            if (mgr->tagRootItem()->findChild(path)->contains(newParent))
//                return false;

//        // move items
//        foreach (const QStringList &path, pathList)
//            //mgr->tagMove(newParent, mgr->tagFind(path));
//            mgr->tagRootItem()->findChild(path)->moveTo(newParent);

//        return true;
//    }
//    else if (data->hasFormat("application/CBookmarkItemList"))
//    {
//        // extrct paths
//        QByteArray encodedData = data->data("application/CBookmarkItemList");
//        QDataStream stream(&encodedData, QIODevice::ReadOnly);
//        QList<QUrl> urlList;
//        int rows = 0;
//        while (!stream.atEnd())
//        {
//            QUrl url;
//            stream >> url;
//            urlList << url;
//            ++rows;
//        }

//        // can we move the items?
//        CBookmarkMgr *mgr = m_rootItem->mgr();
//        foreach (const QUrl &url, urlList)
//            //mgr->bookmarkFind(url)->tagAdd(newParent);
//            newParent->bookmarkAdd(mgr->bookmarkFind(url));

//        return true;
//    }

//    return false;
//}

//QVariant CNavigationItemModel::headerData(int section,
//        Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//    {
//        switch (section)
//        {
//        case 0:
//            return QObject::tr("Name");
//        }
//    }

//    return QVariant();
//}

//QModelIndex CNavigationItemModel::index(int row, int column,
//        const QModelIndex &parent) const
//{
//    if (!hasIndex(row, column, parent) || !m_rootItem)
//        return QModelIndex();

//    CTagItem *parentItem = m_rootItem;
//    if (parent.isValid())
//        parentItem = static_cast<CTagItem *>(parent.internalPointer());

//    CTagItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);

//    return QModelIndex();
//}

//QModelIndex CNavigationItemModel::parent(const QModelIndex &index) const
//{
//    if (!index.isValid() || !m_rootItem)
//        return QModelIndex();

//    CTagItem *childItem = static_cast<CTagItem *>(index.internalPointer());
//    CTagItem *parentItem = childItem->parent();

//    if (parentItem == m_rootItem)
//        return QModelIndex();

//    return createIndex(parentItem->index(), 0, parentItem);
//}

//int CNavigationItemModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.column() > 0 || !m_rootItem)
//        return 0;

//    CTagItem *parentItem = m_rootItem;
//    if (parent.isValid())
//        parentItem = static_cast<CTagItem *>(parent.internalPointer());

//    return parentItem->childCount();
//}

//int CNavigationItemModel::columnCount(const QModelIndex &/*parent*/) const
//{
//    return 1;
//}

//void CNavigationItemModel::bookmarkmgr_tagInserted(CTagItem *parent, int index)
//{
//    if (parent == m_rootItem)
//        beginInsertRows(QModelIndex(), index, index);
//    else
//        beginInsertRows(createIndex(parent->index(), 0, parent), index, index);
//    endInsertRows();
//}

//void CNavigationItemModel::bookmarkmgr_tagRemoved(CTagItem *parent, int index)
//{
//    if (parent == m_rootItem)
//        beginRemoveRows(QModelIndex(), index, index);
//    else
//        beginRemoveRows(createIndex(parent->index(), 0, parent), index, index);
//    endRemoveRows();
//}

//void CNavigationItemModel::bookmarkmgr_tagMoved(CTagItem *oldParent,
//        int oldIndex, CTagItem *newParent, int newIndex)
//{
//    QModelIndex ox;
//    QModelIndex nx;
//    if (oldParent != m_rootItem)
//        ox = createIndex(oldParent->index(), 0, oldParent);
//    if (newParent != m_rootItem)
//        nx = createIndex(newParent->index(), 0, newParent);

//    beginMoveRows(ox, oldIndex, oldIndex, nx, newIndex);
//    endMoveRows();


//}

//void CNavigationItemModel::bookmarkmgr_tagDataChanged(CTagItem *parent, int index)
//{
//    emit dataChanged(createIndex(index, 0, parent),
//                     createIndex(index,  columnCount()-1, parent));
//}

//void CNavigationItemModel::bookmarkmgr_destroyed()
//{
//    m_rootItem = 0;
//}
