#ifndef CTAG_H
#define CTAG_H

#include <QSharedDataPointer>
#include <QString>


class CTagData : public QSharedData
{
public:
    QString name;
};

class CTag
{
public:
    CTag();
    CTag(const CTag &);
    CTag &operator=(const CTag &);
    ~CTag();

    inline const QString &name() const;
    void setName(const QString &name);
private:
    QSharedDataPointer<CTagData> data;
};

const QString &CTag::name() const
{
    return data->name;
}

#endif // CTAG_H
