#include "cbookmarkmgr.h"

CBookmarkMgr::CBookmarkMgr(QObject *parent) : QObject(parent)
{
    m_tagRootItem = new CTagItem(this);
}

CBookmarkMgr::~CBookmarkMgr()
{
    bookmarkRemoveAll();
    m_tagRootItem->removeAll();
    delete m_tagRootItem;
}

int CBookmarkMgr::bookmarkCount() const
{
    return m_bookmarkItems.count();
}

int CBookmarkMgr::bookmarkIndexOf(const QUrl &url) const
{
    for (int i = 0; i < m_bookmarkItems.count(); ++i)
        if (m_bookmarkItems.at(i)->data().url() == url)
            return i;
    return -1;
}

int CBookmarkMgr::bookmarkIndexOf(CBookmarkItem *item) const
{
    return m_bookmarkItems.indexOf(item);
}

CBookmarkItem *CBookmarkMgr::bookmarkAt(int index) const
{
    return m_bookmarkItems.value(index);
}

CBookmarkItem *CBookmarkMgr::bookmarkFind(const QUrl &url) const
{
    int index = bookmarkIndexOf(url);
    if (index == -1)
        return 0;
    return m_bookmarkItems.value(index);
}

CBookmarkItem *CBookmarkMgr::bookmarkAdd(const CBookmark &data)
{
    if (bookmarkFind(data.url()))
        return 0;

    CBookmarkItem *item = new CBookmarkItem(data, this);
    m_bookmarkItems.push_back(item);
    emit bookmarkInserted(item);
    return item;
}

CBookmarkItem *CBookmarkMgr::bookmarkAddOrReplace(const CBookmark &data)
{
    CBookmarkItem *item = bookmarkFind(data.url());
    if (item)
    {
        item->setData(data);
    }
    else
    {
        item = new CBookmarkItem(data, this);
        m_bookmarkItems.push_back(item);
        emit bookmarkInserted(item);
    }
    return item;
}

void CBookmarkMgr::bookmarkRemove(CBookmarkItem *item)
{
    int index = bookmarkIndexOf(item);
    if (index == -1)
        return;
    bookmarkRemoveAt(index);
}

void CBookmarkMgr::bookmarkRemove(const QUrl &url)
{
    int index = bookmarkIndexOf(url);
    if (index == -1)
        return;
    bookmarkRemoveAt(index);
}

void CBookmarkMgr::bookmarkRemoveAt(int index)
{
    CBookmarkItem *item = m_bookmarkItems.takeAt(index);
    emit bookmarkRemoved(item);
    delete item;
}

void CBookmarkMgr::bookmarkRemoveAll()
{
    while (m_bookmarkItems.count())
    {
        CBookmarkItem *item = m_bookmarkItems.takeLast();
        emit bookmarkRemoved(item);
        delete item;
    }
}

CTagItem *CBookmarkMgr::tagRootItem() const
{
    return m_tagRootItem;
}

void CBookmarkMgr::callbackBookmarkDataChanged(CBookmarkItem *item)
{
    emit bookmarkDataChanged(item);
}

void CBookmarkMgr::callbackTagInserted(CTagItem *parent, CTagItem *item)
{
    emit tagInserted(parent, item);
}

void CBookmarkMgr::callbackTagRemoved(CTagItem *parent, CTagItem *item)
{
    emit tagRemoved(parent, item);
}

void CBookmarkMgr::callbackTagMoved(CTagItem *oldParent, CTagItem *newParent,
        CTagItem *item)
{
    emit tagMoved(oldParent, newParent, item);
}

void CBookmarkMgr::callbackTagDataChanged(CTagItem *parent, CTagItem *item)
{
    emit tagDataChanged(parent, item);
}
