#ifndef CBOOKMARK_H
#define CBOOKMARK_H

#include <QSharedDataPointer>
#include <QUrl>


class CBookmarkData : public QSharedData
{
public:
    QUrl url;
    QString name;
};

class CBookmark
{
public:
    CBookmark();
    CBookmark(const CBookmark &);
    CBookmark &operator=(const CBookmark &);
    ~CBookmark();

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    inline const QString &name() const;
    void setName(const QString &name);
private:
    QSharedDataPointer<CBookmarkData> data;
};

const QUrl &CBookmark::url() const
{
    return data->url;
}

const QString &CBookmark::name() const
{
    return data->name;
}

#endif // CBOOKMARK_H
