#ifndef CTAGDATA_H
#define CTAGDATA_H

#include <QSharedDataPointer>
#include <QString>


class CTagDataData : public QSharedData
{
public:
    QString name;
};

class CTagData
{
public:
    CTagData();
    CTagData(const CTagData &);
    CTagData &operator=(const CTagData &);
    ~CTagData();

    inline const QString &name() const;
    void setName(const QString &name);
private:
    QSharedDataPointer<CTagDataData> data;
};

const QString &CTagData::name() const
{
    return data->name;
}

#endif // CTAGDATA_H
