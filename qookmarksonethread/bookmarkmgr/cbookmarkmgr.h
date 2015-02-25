#ifndef CBOOKMARKMGR_H
#define CBOOKMARKMGR_H

#include <QObject>
#include "cbookmarkitem.h"

class CBookmarkMgr : public QObject
{
    Q_OBJECT
    friend class CBookmarkItem;
public:
    explicit CBookmarkMgr(QObject *parent = 0);
    ~CBookmarkMgr();

    int count() const;
    int indexOf(const QUrl &url) const;
    CBookmarkItem *value(int index) const;
    CBookmarkItem *find(const QUrl &url) const;
    CBookmarkItem *insert(const CBookmarkData &data);
    void remove(CBookmarkItem *item);
    void remove(const QUrl &url);
    void removeAt(int index);
    void removeAll();
signals:
    void bookmarkInserted(CBookmarkItem *item);
    void bookmarkRemoved(CBookmarkItem *item);
    void bookmarkDataChanged(CBookmarkItem *item);
private:
    void callbackBookmarkDataChanged(CBookmarkItem *item);
private:
    QList<CBookmarkItem *> m_items;
};


#endif // CBOOKMARKMGR_H
