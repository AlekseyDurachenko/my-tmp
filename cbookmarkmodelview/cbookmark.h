#ifndef CBOOKMARK_H
#define CBOOKMARK_H

#include <QSharedDataPointer>
#include <QUrl>


class CBookmarkData : public QSharedData
{
public:
    int id;
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

    inline int id() const;
    void setId(int id);

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    inline const QString &name() const;
    void setName(const QString &name);
private:
    QSharedDataPointer<CBookmarkData> data;
};

int CBookmark::id() const
{
    return data->id;
}

const QUrl &CBookmark::url() const
{
    return data->url;
}

const QString &CBookmark::name() const
{
    return data->name;
}

#endif // CBOOKMARK_H
