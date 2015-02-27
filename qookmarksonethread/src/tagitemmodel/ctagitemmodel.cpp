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
#include "ctagitemmodel.h"
#include "cbookmarkmgr.h"
#include <QMimeData>
#include <QDebug>


CTagItemModel::CTagItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_rootItem = 0;
    setRootItem(0);
}

CTagItemModel::CTagItemModel(CTagItem *rootItem, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_rootItem = 0;
    setRootItem(rootItem);
}

void CTagItemModel::setRootItem(CTagItem *rootItem)
{
    beginResetModel();

    if (m_rootItem)
        disconnect(m_rootItem->mgr(), 0, this, 0);

    m_rootItem = rootItem;
    if (m_rootItem)
    {
        connect(m_rootItem->mgr(), SIGNAL(tagInserted(CTagItem *,int)),
                this, SLOT(bookmarkmgr_tagInserted(CTagItem *,int)));
        connect(m_rootItem->mgr(), SIGNAL(tagRemoved(CTagItem *,int)),
                this, SLOT(bookmarkmgr_tagRemoved(CTagItem *,int)));
        connect(m_rootItem->mgr(), SIGNAL(tagMoved(CTagItem *,int,CTagItem *,int)),
                this, SLOT(bookmarkmgr_tagMoved(CTagItem *,int,CTagItem *,int)));
        connect(m_rootItem->mgr(), SIGNAL(tagDataChanged(CTagItem *,int)),
                this, SLOT(bookmarkmgr_tagDataChanged(CTagItem *,int)));
        connect(m_rootItem->mgr(), SIGNAL(destroyed()),
                this, SLOT(bookmarkmgr_destroyed()));
    }

    endResetModel();
}

QVariant CTagItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_rootItem)
        return QVariant();

    CTagItem *item = static_cast<CTagItem *>(index.internalPointer());
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
        if (index.column() == 0)
            return item->data().name();

//    if (role == Qt::DecorationRole)
//        if (index.column() == 0)
//            return item->icon();

    if (role == Qt::UserRole)
        return QVariant::fromValue(index.internalPointer());

    return QVariant();
}

Qt::ItemFlags CTagItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    //CTagItem *item = static_cast<CTagItem *>(index.internalPointer());
    //if (item->type() == CTagItem::Tag)
        return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled;
    //else
    //    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDropEnabled;
}

QStringList CTagItemModel::mimeTypes() const
{
    return QStringList() << "application/CTagItemList"
                         << "application/CBookmarkItemList";
}

QMimeData *CTagItemModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();

    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes)
        if (index.isValid() && index.column() == 0)
            stream << static_cast<CTagItem *>(index.internalPointer())->path();

    mimeData->setData("application/CTagItemList", encodedData);
    return mimeData;
}

bool CTagItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
        int /*row*/, int /*column*/, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    // new parent for the items
    CTagItem *newParent = static_cast<CTagItem *>(parent.internalPointer());
    if (!newParent)
        return false;

    if (data->hasFormat("application/CTagItemList"))
    {
        // extrct paths
        QByteArray encodedData = data->data("application/CTagItemList");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QList<QStringList> pathList;
        int rows = 0;
        while (!stream.atEnd())
        {
            QStringList path;
            stream >> path;
            pathList << path;
            ++rows;
        }

        // can we move the items?
        CBookmarkMgr *mgr = m_rootItem->mgr();
        foreach (const QStringList &path, pathList)
            //if (!mgr->tagCanMove(newParent, mgr->tagFind(path)))
            if (mgr->tagRootItem()->findChild(path)->contains(newParent))
                return false;

        // move items
        foreach (const QStringList &path, pathList)
            //mgr->tagMove(newParent, mgr->tagFind(path));
            mgr->tagRootItem()->findChild(path)->moveTo(newParent);

        return true;
    }
    else if (data->hasFormat("application/CBookmarkItemList"))
    {
        // extrct paths
        QByteArray encodedData = data->data("application/CBookmarkItemList");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        QList<QUrl> urlList;
        int rows = 0;
        while (!stream.atEnd())
        {
            QUrl url;
            stream >> url;
            urlList << url;
            ++rows;
        }

        // can we move the items?
        CBookmarkMgr *mgr = m_rootItem->mgr();
        foreach (const QUrl &url, urlList)
            //mgr->bookmarkFind(url)->tagAdd(newParent);
            newParent->bookmarkAdd(mgr->bookmarkFind(url));

        return true;
    }

    return false;
}

QVariant CTagItemModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case 0:
            return QObject::tr("Name");
        }
    }

    return QVariant();
}

QModelIndex CTagItemModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || !m_rootItem)
        return QModelIndex();

    CTagItem *parentItem = m_rootItem;
    if (parent.isValid())
        parentItem = static_cast<CTagItem *>(parent.internalPointer());

    CTagItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex CTagItemModel::parent(const QModelIndex &index) const
{
    if (!index.isValid() || !m_rootItem)
        return QModelIndex();

    CTagItem *childItem = static_cast<CTagItem *>(index.internalPointer());
    CTagItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->index(), 0, parentItem);
}

int CTagItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0 || !m_rootItem)
        return 0;

    CTagItem *parentItem = m_rootItem;
    if (parent.isValid())
        parentItem = static_cast<CTagItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int CTagItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}

void CTagItemModel::bookmarkmgr_tagInserted(CTagItem *parent, int index)
{
    if (parent == m_rootItem)
        beginInsertRows(QModelIndex(), index, index);
    else
        beginInsertRows(createIndex(parent->index(), 0, parent), index, index);
    endInsertRows();
}

void CTagItemModel::bookmarkmgr_tagRemoved(CTagItem *parent, int index)
{
    if (parent == m_rootItem)
        beginRemoveRows(QModelIndex(), index, index);
    else
        beginRemoveRows(createIndex(parent->index(), 0, parent), index, index);
    endRemoveRows();
}

void CTagItemModel::bookmarkmgr_tagMoved(CTagItem *oldParent,
        int oldIndex, CTagItem *newParent, int newIndex)
{
    QModelIndex ox;
    QModelIndex nx;
    if (oldParent != m_rootItem)
        ox = createIndex(oldParent->index(), 0, oldParent);
    if (newParent != m_rootItem)
        nx = createIndex(newParent->index(), 0, newParent);

    beginMoveRows(ox, oldIndex, oldIndex, nx, newIndex);
    endMoveRows();


}

void CTagItemModel::bookmarkmgr_tagDataChanged(CTagItem *parent, int index)
{
    emit dataChanged(createIndex(index, 0, parent),
                     createIndex(index,  columnCount()-1, parent));
}

void CTagItemModel::bookmarkmgr_destroyed()
{
    m_rootItem = 0;
}
