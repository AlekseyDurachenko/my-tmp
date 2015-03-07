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
#ifndef CNAVIGATIONITEMMODEL_H
#define CNAVIGATIONITEMMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QHash>
class CTagMgr;
class CTagItem;


class CNavigationItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CNavigationItemModel(QObject *parent = 0);
    explicit CNavigationItemModel(CTagMgr *tagMgr, QObject *parent = 0);
    virtual ~CNavigationItemModel();

    inline CTagMgr *tagMgr() const;
    void setTagMgr(CTagMgr *tagMgr);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QStringList mimeTypes() const;
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
private slots:
    void tagMgr_aboutToBeInserted(CTagItem *parent ,int first, int last);
    void tagMgr_inserted(CTagItem *parent, int first, int last);
    void tagMgr_aboutToBeRemoved(CTagItem *parent, int first, int last);
    void tagMgr_removed(CTagItem *parent, int first, int last);
    void tagMgr_aboutToBeMoved(CTagItem *srcParent, int srcFirst, int srcLast,
                               CTagItem *dstParent, int dstIndex);
    void tagMgr_moved(CTagItem *srcParent, int srcFirst, int srcLast,
                      CTagItem *dstParent, int dstIndex);
    void tagMgr_dataChanged(CTagItem *item);
    void tagMgr_bookmarksChanged(CTagItem *item);
    void tagMgr_destroyed();
private:
    enum TopLevelItem { Favorites, Rated, ReadLater, BookmarksRoot, Trash };
private:
    void initTopLevelItems();
    void initTopLevelCounters();
    int bookmarksIndex() const;
    QVariant topLevelData(const QModelIndex &index, int role) const;
    QString topLevelName(TopLevelItem item) const;
    QIcon topLevelIcon(TopLevelItem item) const;
    void recalcTopLevelCounters();
private:
    CTagMgr *m_tagMgr;
    QVector<TopLevelItem> m_topLevelItems;
    QHash<TopLevelItem, int> m_topLevelCounter;
};

CTagMgr *CNavigationItemModel::tagMgr() const
{
    return m_tagMgr;
}


#endif // CNAVIGATIONITEMMODEL_H
