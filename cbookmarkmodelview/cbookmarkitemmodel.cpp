// Copyright 2014, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#include "cbookmarkitemmodel.h"
#include <QIcon>
#include <QMimeData>
#include <QDebug>


CBookmarkItemModel::CBookmarkItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_bookmarkRepresentation = 0;
}

CBookmarkItemModel::CBookmarkItemModel(CBookmarkRepresentation *bookmarkRepresentaion, QObject *parent) :
    QAbstractItemModel(parent)
{
    m_bookmarkRepresentation = 0;
    setBookmarkRepresentaion(bookmarkRepresentaion);
}

void CBookmarkItemModel::setBookmarkRepresentaion(CBookmarkRepresentation *bookmarkRepresentaion)
{
    beginResetModel();

    if (m_bookmarkRepresentation)
        disconnect(m_bookmarkRepresentation, 0, this, 0);

    m_bookmarkRepresentation = bookmarkRepresentaion;
    if (m_bookmarkRepresentation)
    {
        connect(m_bookmarkRepresentation, SIGNAL(inserted(int,int)),
                this, SLOT(bookmark_inserted(int,int)));
        connect(m_bookmarkRepresentation, SIGNAL(removed(int,int)),
                this, SLOT(bookmark_removed(int,int)));
        connect(m_bookmarkRepresentation, SIGNAL(dataChanged(int,int)),
                this, SLOT(bookmark_dataChanged(int,int)));
    }

    endResetModel();
}

QVariant CBookmarkItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !m_bookmarkRepresentation)
        return QVariant();

    const CBookmark &bookmark = m_bookmarkRepresentation->at(index.row());
    if (role == Qt::DisplayRole || role == Qt::ToolTipRole)
    {
        switch (index.column())
        {
        case 0:
            return bookmark.id();
        case 1:
            return bookmark.url();
        case 2:
            return bookmark.name();
        }
    }

    return QVariant();
}

Qt::ItemFlags CBookmarkItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    Qt::ItemFlags f = Qt::ItemIsEnabled
            |Qt::ItemIsSelectable;

    return f;
}

QVariant CBookmarkItemModel::headerData(int section,
        Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0:
            return tr("Id");
        case 1:
            return tr("Url");
        case 2:
            return tr("Name");
        }
    }

    return QVariant();
}

QModelIndex CBookmarkItemModel::index(int row, int column,
        const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || !m_bookmarkRepresentation)
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex CBookmarkItemModel::parent(const QModelIndex &/*index*/) const
{
    return QModelIndex();
}

int CBookmarkItemModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_bookmarkRepresentation)
        return 0;

    return m_bookmarkRepresentation->count();
}

int CBookmarkItemModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 3;
}

void CBookmarkItemModel::bookmark_inserted(int first, int last)
{
    beginInsertRows(QModelIndex(), first, last);
    endInsertRows();
}

void CBookmarkItemModel::bookmark_removed(int first, int last)
{
    beginRemoveRows(QModelIndex(), first, last);
    endRemoveRows();
}

void CBookmarkItemModel::bookmark_dataChanged(int first, int last)
{
    emit dataChanged(createIndex(first, 0),
                     createIndex(last, columnCount()-1));
}

void CBookmarkItemModel::bookmark_destroyed()
{
    m_bookmarkRepresentation = 0;
}
