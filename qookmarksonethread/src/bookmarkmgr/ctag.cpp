#include "ctag.h"



CTag::CTag() : data(new CTagData)
{

}

CTag::CTag(const CTag &rhs) : data(rhs.data)
{

}

CTag &CTag::operator=(const CTag &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

CTag::~CTag()
{

}

void CTag::setName(const QString &name)
{
    data->name = name;
}

