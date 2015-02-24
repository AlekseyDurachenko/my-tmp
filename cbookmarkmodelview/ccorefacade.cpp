#include "ccorefacade.h"

CCoreFacade::CCoreFacade(QObject *parent) : QObject(parent)
{
    m_coreThread = new QThread(this);
    m_coreThread->start();

    m_bookmarkRepresentationOrigin = new CBookmarkRepresentationOrigin;
    m_bookmarkRepresentationOrigin->moveToThread(m_coreThread);
}

CCoreFacade::~CCoreFacade()
{
    m_coreThread->quit();
    m_coreThread->wait();
    delete m_coreThread;
}

CBookmarkRepresentation *CCoreFacade::createBookmarkRepresentation()
{
    CBookmarkRepresentation *bookmarkRep = new CBookmarkRepresentation(this);
    connect(m_bookmarkRepresentationOrigin, SIGNAL(changed(CBookmark)),
            bookmarkRep, SLOT(origin_changed(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(changed(QList<CBookmark>)),
            bookmarkRep, SLOT(origin_changed(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(inserted(CBookmark)),
            bookmarkRep, SLOT(origin_inserted(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(inserted(QList<CBookmark>)),
            bookmarkRep, SLOT(origin_inserted(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(removed(CBookmark)),
            bookmarkRep, SLOT(origin_removed(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(removed(QList<CBookmark>)),
            bookmarkRep, SLOT(origin_removed(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(initialized(QList<CBookmark>)),
            bookmarkRep, SLOT(origin_initialized(QList<CBookmark>)));

    return bookmarkRep;
}
