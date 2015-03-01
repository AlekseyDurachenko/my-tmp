// Copyright 2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef CBOOKMARKFILTER_H
#define CBOOKMARKFILTER_H

#include <QSharedDataPointer>
#include <QSet>
class CTagItem;


namespace Bookmark {
    enum FilterOption {
        Any             = 0xFFFF,
        ReadLater       = 0x0001,
        NotReadLater    = 0x0100,
        Favorite        = 0x0002,
        NotFavorite     = 0x0200,
        Trash           = 0x0004,
        NotTrash        = 0x0400
    };
    Q_DECLARE_FLAGS(FilterOptions, FilterOption)
}
Q_DECLARE_OPERATORS_FOR_FLAGS(Bookmark::FilterOptions)


class CBookmarkFilterData : public QSharedData
{
public:
    Bookmark::FilterOptions inclusiveFlags;
    int minRating;
    int maxRating;
    QSet<CTagItem *> tags;
};


class CBookmarkFilter
{
public:
    CBookmarkFilter();
    CBookmarkFilter(const CBookmarkFilter &);
    CBookmarkFilter &operator=(const CBookmarkFilter &);
    ~CBookmarkFilter();

    inline const Bookmark::FilterOptions &inclusiveOptionFilter() const;
    void setInclusiveOptionFilter(const Bookmark::FilterOptions &optionFilter);

    inline int minRating() const;
    inline int maxRating() const;
    void setRatingRange(int min, int max);

    inline const QSet<CTagItem *> tags() const;
    void setTags(const QSet<CTagItem *> &tags);
private:
    QSharedDataPointer<CBookmarkFilterData> data;
};

const Bookmark::FilterOptions &CBookmarkFilter::inclusiveOptionFilter() const
{
    return data->inclusiveFlags;
}

int CBookmarkFilter::minRating() const
{
    return data->minRating;
}

int CBookmarkFilter::maxRating() const
{
    return data->maxRating;
}

const QSet<CTagItem *> CBookmarkFilter::tags() const
{
    return data->tags;
}


#endif // CBOOKMARKFILTER_H
