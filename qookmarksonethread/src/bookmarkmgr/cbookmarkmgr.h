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

    CTagItem *tagRootItem() const;
    CTagItem *tagAdd(CTagItem *parent, const CTag &data);
    void tagMove(CTagItem *newParent, CTagItem *item);
    void tagRemove(CTagItem *item);
    void tagRemoveAll();
signals:
    void bookmarkInserted(CBookmarkItem *item);
    void bookmarkRemoved(CBookmarkItem *item);
    void bookmarkDataChanged(CBookmarkItem *item);

    void tagInserted(CTagItem *parent, CTagItem* item);
    void tagRemoved(CTagItem *parent, CTagItem* item);
    void tagMoved(CTagItem *oldParent, CTagItem *newParent, CTagItem *item);
    void tagDataChanged(CTagItem *parent, CTagItem* item);
private:
    void callbackBookmarkDataChanged(CBookmarkItem *item);
    void callbackTagDataChanged(CTagItem *parent, CTagItem *item);
private:
    QList<CBookmarkItem *> m_bookmarkItems;
    CTagItem *m_tagRootItem;
};


#endif // CBOOKMARKMGR_H
