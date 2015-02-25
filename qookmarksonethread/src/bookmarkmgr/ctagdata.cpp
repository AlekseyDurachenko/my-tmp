#include "ctagdata.h"



CTagData::CTagData() : data(new CTagDataData)
{

}

CTagData::CTagData(const CTagData &rhs) : data(rhs.data)
{

}

CTagData &CTagData::operator=(const CTagData &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

CTagData::~CTagData()
{

}

void CTagData::setName(const QString &name)
{
    data->name = name;
}

