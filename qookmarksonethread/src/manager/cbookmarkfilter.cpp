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
#include "cbookmarkfilter.h"
#include "consts.h"


CBookmarkFilter::CBookmarkFilter() : data(new CBookmarkFilterData)
{
    data->inclusiveFlags = ~Bookmark::FilterOptions(Bookmark::Trash);
    data->minRating = Bookmark::MinimumRating;
    data->minRating = Bookmark::MaximumRating;
}

CBookmarkFilter::CBookmarkFilter(const CBookmarkFilter &rhs) : data(rhs.data)
{
}

CBookmarkFilter &CBookmarkFilter::operator=(const CBookmarkFilter &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

CBookmarkFilter::~CBookmarkFilter()
{
}

void CBookmarkFilter::setInclusiveOptionFilter(const Bookmark::FilterOptions &optionFilter)
{
    data->inclusiveFlags = optionFilter;
}

void CBookmarkFilter::setRatingRange(int min, int max)
{
    data->minRating = qMin(min, max);
    data->maxRating = qMax(min, max);
}

void CBookmarkFilter::setTags(const QSet<CTagItem *> &tags)
{
    data->tags = tags;
}
