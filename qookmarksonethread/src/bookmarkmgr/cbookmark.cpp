#include "cbookmark.h"


CBookmark::CBookmark() : data(new CBookmarkData)
{

}

CBookmark::CBookmark(const CBookmark &rhs) : data(rhs.data)
{

}

CBookmark &CBookmark::operator=(const CBookmark &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

CBookmark::~CBookmark()
{

}

void CBookmark::setUrl(const QUrl &url)
{
    data->url = url;
}

void CBookmark::setName(const QString &name)
{
    data->name = name;
}
