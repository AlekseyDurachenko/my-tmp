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

    CBookmarkRepresentation *createBookmarkRepresentation();
private:
    QThread *m_coreThread;
    CBookmarkRepresentationOrigin *m_bookmarkRepresentationOrigin;
};

#endif // CCOREFACADE_H
