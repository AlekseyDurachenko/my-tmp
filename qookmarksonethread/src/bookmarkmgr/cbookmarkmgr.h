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
    CBookmarkItem *bookmarkAdd(const CBookmark &data, const QSet<CTagItem *> &tags = QSet<CTagItem *>());
    void bookmarkRemove(CBookmarkItem *item);   // need??
    void bookmarkRemove(const QUrl &url);
    void bookmarkRemoveAt(int index);           // need??
    void bookmarkRemoveAll();
signals:
    void bookmarkInserted(CBookmarkItem *item);
    void bookmarkRemoved(CBookmarkItem *item);
    void bookmarkDataChanged(CBookmarkItem *item);

    void tagInserted(CTagItem *parent, CTagItem* tag);
    void tagRemoved(CTagItem *parent, CTagItem* tag);
    void tagDataChanged(CTagItem *parent, CTagItem* tag);
private:
    void callbackBookmarkDataChanged(CBookmarkItem *item);
    void callbackTagDataChanged(CTagItem *parent, CTagItem *tag);
private:
    QList<CBookmarkItem *> m_bookmarkItems;
};


#endif // CBOOKMARKMGR_H
