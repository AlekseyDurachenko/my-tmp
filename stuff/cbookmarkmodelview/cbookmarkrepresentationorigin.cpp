#include "cbookmarkrepresentationorigin.h"
#include <QDebug>

CBookmarkRepresentationOrigin::CBookmarkRepresentationOrigin(QObject *parent) :
    QObject(parent)
{
    connect(&m_test, SIGNAL(timeout()), this, SLOT(timeout()));
    m_test.setInterval(2000);
    m_test.start();
}

CBookmarkRepresentationOrigin::~CBookmarkRepresentationOrigin()
{
}

void CBookmarkRepresentationOrigin::timeout()
{
    CBookmark b1;
    b1.setId(1);
    b1.setName("abc");
    b1.setUrl(QUrl("http://ya.ru/"));

    qDebug() << "insert emited";

    emit inserted(b1);
}
