#ifndef CBOOKMARKREPRESENTATION_H
#define CBOOKMARKREPRESENTATION_H

#include <QObject>
#include <QList>
#include "cbookmark.h"


class CBookmarkRepresentation : public QObject
{
    Q_OBJECT
public:
    explicit CBookmarkRepresentation(QObject *parent = 0);
    virtual ~CBookmarkRepresentation();

    inline int count() const;
    inline const CBookmark &at(int i) const;
signals:
    void inserted(int first, int last);
    void removed(int first, int last);
    void changed(int first, int last);
    void reseted();
public slots:
    void origin_inserted(const CBookmark &bookmark);
    void origin_inserted(const QList<CBookmark> &bookmarks);
    void origin_removed(const CBookmark &bookmark);
    void origin_removed(const QList<CBookmark> &bookmarks);
    void origin_changed(const CBookmark &bookmark);
    void origin_changed(const QList<CBookmark> &bookmarks);
    void origin_initialized(const QList<CBookmark> &bookmarks);
private:
    QList<CBookmark> m_bookmarks;
};

int CBookmarkRepresentation::count() const
{
    return m_bookmarks.count();
}

const CBookmark &CBookmarkRepresentation::at(int i) const
{
    return m_bookmarks.at(i);
}


#endif // CBOOKMARKREPRESENTATION_H
