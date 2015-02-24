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
#ifndef CBOOKMARKITEMMODEL_H
#define CBOOKMARKITEMMODEL_H

#include "cbookmarkrepresentation.h"
#include <QAbstractItemModel>


class CBookmarkItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CBookmarkItemModel(QObject *parent = 0);
    explicit CBookmarkItemModel(CBookmarkRepresentation *bookmarkRepresentaion, QObject *parent = 0);

    inline CBookmarkRepresentation *bookmarkRepresentaion() const;
    void setBookmarkRepresentaion(CBookmarkRepresentation *bookmarkRepresentaion);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
private slots:
    void bookmark_inserted(int first, int last);
    void bookmark_removed(int first, int last);
    void bookmark_dataChanged(int first, int last);
    void bookmark_destroyed();
private:
    CBookmarkRepresentation *m_bookmarkRepresentation;
};

CBookmarkRepresentation *CBookmarkItemModel::bookmarkRepresentaion() const
{
    return m_bookmarkRepresentation;
}


#endif // CBOOKMARKITEMMODEL_H
