#include "cbookmarkrepresentation.h"

CBookmarkRepresentation::CBookmarkRepresentation(QObject *parent) :
    QObject(parent)
{
}

CBookmarkRepresentation::~CBookmarkRepresentation()
{
}

void CBookmarkRepresentation::origin_inserted(const CBookmark &bookmark)
{
    origin_inserted(QList<CBookmark>() << bookmark);
}

void CBookmarkRepresentation::origin_inserted(const QList<CBookmark> &bookmarks)
{
    m_bookmarks << bookmarks;
    emit inserted(m_bookmarks.count()-bookmarks.count()-1, m_bookmarks.count()-1);
}

void CBookmarkRepresentation::origin_removed(const CBookmark &bookmark)
{
    origin_removed(QList<CBookmark>() << bookmark);
}

void CBookmarkRepresentation::origin_removed(const QList<CBookmark> &bookmarks)
{
    foreach (const CBookmark &bookmark, bookmarks)
    {
        for (int i = 0; i < m_bookmarks.count(); ++i)
        {
            if (m_bookmarks.at(i).id() == bookmark.id())
            {
                m_bookmarks.removeAt(i);
                emit removed(i, i);
            }
        }
    }
}

void CBookmarkRepresentation::origin_changed(const CBookmark &bookmark)
{
    origin_changed(QList<CBookmark>() << bookmark);
}

void CBookmarkRepresentation::origin_changed(const QList<CBookmark> &bookmarks)
{
    foreach (const CBookmark &bookmark, bookmarks)
    {
        for (int i = 0; i < m_bookmarks.count(); ++i)
        {
            if (m_bookmarks.at(i).id() == bookmark.id())
            {
                m_bookmarks.replace(i, bookmark);
                emit changed(i, i);
            }
        }
    }
}

void CBookmarkRepresentation::origin_initialized(const QList<CBookmark> &bookmarks)
{
    m_bookmarks = bookmarks;
    emit reseted();
}
