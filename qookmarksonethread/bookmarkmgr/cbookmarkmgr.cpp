#include "cbookmarkmgr.h"

CBookmarkMgr::CBookmarkMgr(QObject *parent) : QObject(parent)
{

}

CBookmarkMgr::~CBookmarkMgr()
{

}

int CBookmarkMgr::count() const
{
    return m_items.count();
}

int CBookmarkMgr::indexOf(const QUrl &url) const
{
    for (int i = 0; i < m_items.count(); ++i)
        if (m_items.at(i)->data().url() == url)
            return i;
    return -1;
}

CBookmarkItem *CBookmarkMgr::value(int index) const
{
    return m_items.value(index);
}

CBookmarkItem *CBookmarkMgr::find(const QUrl &url) const
{
    int index = indexOf(url);
    if (index == -1)
        return 0;
    return m_items.value(index);
}

void CBookmarkMgr::remove(CBookmarkItem *item)
{
    m_items.removeAll(item);
}

void CBookmarkMgr::remove(const QUrl &url)
{
    int index = indexOf(url);
    if (index == -1)
        return;
    removeAt(index);
}

void CBookmarkMgr::removeAt(int index)
{
    m_items.removeAt(index);
}

void CBookmarkMgr::removeAll()
{
    m_items.clear();
}

void CBookmarkMgr::callbackBookmarkDataChanged(CBookmarkItem *item)
{
    Q_UNUSED(item);
}
