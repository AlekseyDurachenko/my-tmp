#ifndef CCOREFACADE_H
#define CCOREFACADE_H

#include <QObject>
#include <QThread>
#include "cbookmarkrepresentation.h"
#include "cbookmarkrepresentationorigin.h"


class CCoreFacade : public QObject
{
    Q_OBJECT
public:
    explicit CCoreFacade(QObject *parent = 0);
    virtual ~CCoreFacade();

    inline CBookmarkRepresentation *bookmarkRepresentation() const;
private:
    QThread *m_coreThread;
    CBookmarkRepresentationOrigin *m_bookmarkRepresentationOrigin;
    CBookmarkRepresentation *m_bookmarkRepresentation;
};

CBookmarkRepresentation *CCoreFacade::bookmarkRepresentation() const
{
    return m_bookmarkRepresentation;
}


#endif // CCOREFACADE_H
