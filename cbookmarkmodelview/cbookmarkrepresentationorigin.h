#ifndef CBOOKMARKREPRESENTATIONORIGIN_H
#define CBOOKMARKREPRESENTATIONORIGIN_H

#include <QObject>
#include <QList>
#include <QTimer>
#include "cbookmark.h"


class CBookmarkRepresentationOrigin : public QObject
{
    Q_OBJECT
public:
    explicit CBookmarkRepresentationOrigin(QObject *parent = 0);
    virtual ~CBookmarkRepresentationOrigin();
signals:
    void inserted(const CBookmark &bookmark);
    void inserted(const QList<CBookmark> &bookmarks);
    void removed(const CBookmark &bookmark);
    void removed(const QList<CBookmark> &bookmarks);
    void changed(const CBookmark &bookmark);
    void changed(const QList<CBookmark> &bookmarks);
    void initialized(const QList<CBookmark> &bookmarks);
private slots:
    void timeout();
private:
    QList<CBookmark> m_bookmarks;
    QTimer m_test;
};


#endif // CBOOKMARKREPRESENTATIONORIGIN_H
