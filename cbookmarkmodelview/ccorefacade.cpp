#include "ccorefacade.h"

CCoreFacade::CCoreFacade(QObject *parent) : QObject(parent)
{
    m_coreThread = new QThread(this);
    m_coreThread->start();

    m_bookmarkRepresentationOrigin = new CBookmarkRepresentationOrigin;
    m_bookmarkRepresentationOrigin->moveToThread(m_coreThread);

    m_bookmarkRepresentation = new CBookmarkRepresentation(this);
    connect(m_bookmarkRepresentationOrigin, SIGNAL(changed(CBookmark)),
            m_bookmarkRepresentation, SLOT(origin_changed(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(changed(QList<CBookmark>)),
            m_bookmarkRepresentation, SLOT(origin_changed(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(inserted(CBookmark)),
            m_bookmarkRepresentation, SLOT(origin_inserted(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(inserted(QList<CBookmark>)),
            m_bookmarkRepresentation, SLOT(origin_inserted(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(removed(CBookmark)),
            m_bookmarkRepresentation, SLOT(origin_removed(CBookmark)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(removed(QList<CBookmark>)),
            m_bookmarkRepresentation, SLOT(origin_removed(QList<CBookmark>)));
    connect(m_bookmarkRepresentationOrigin, SIGNAL(initialized(QList<CBookmark>)),
            m_bookmarkRepresentation, SLOT(origin_initialized(QList<CBookmark>)));
}

CCoreFacade::~CCoreFacade()
{
    m_coreThread->quit();
    m_coreThread->wait();
    delete m_bookmarkRepresentationOrigin;
}
