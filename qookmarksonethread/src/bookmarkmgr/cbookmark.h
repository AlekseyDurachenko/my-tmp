// Copyright 2014-2015, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
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
#ifndef CBOOKMARK_H
#define CBOOKMARK_H

#include <QSharedDataPointer>
#include <QUrl>
#include <QFont>
#include <QColor>
#include <QDateTime>


class CBookmarkData : public QSharedData
{
public:
    // base
    QString title;
    QUrl url;
    QString description;
    // ext
    QString comment;
    QStringList keywordList;
    bool isReadLater;
    bool isFavorite;
    bool isDeleted;
    int rating;
    // style
    QColor textColor;
    QColor textBackgroundColor;
    // meta
    QDateTime createdDateTime;
    QDateTime editedDateTime;
    QDateTime lastVisitedDateTime;
    int visitCount;
    // status
    int httpResponseCode;
    QString httpResponseText;
    QDateTime lastCheckDateTime;
};

class CBookmark
{
public:
    CBookmark();
    CBookmark(const CBookmark &);
    CBookmark &operator=(const CBookmark &);
    ~CBookmark();

    inline const QString &title() const;
    void setTitle(const QString &title);

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    inline const QString &description() const;
    void setDescription(const QString &description);

    inline const QString &comment() const;
    void setComment(const QString &comment);

    inline const QStringList &keywordList() const;
    void setKeywordList(const QStringList &keywordList);

    inline bool isReadLater() const;
    void setReadLater(bool state);

    inline bool isFavorite() const;
    void setFavorite(bool state);

    inline bool isDeleted() const;
    void setDeleted(bool state);

    inline int rating() const;
    void setRating(int rating);

    inline const QColor &textColor() const;
    void setTextColor(const QColor &textColor);

    inline const QColor &textBackgroundColor() const;
    void setTextBackgroundColor(const QColor &textBackgroundColor);

    inline const QDateTime &createdDateTime() const;
    void setCreatedDateTime(const QDateTime &createdDateTime);

    inline const QDateTime &editedDateTime() const;
    void setEditedDateTime(const QDateTime &editedDateTime);

    inline const QDateTime &lastVisitedDateTime() const;
    void setLastVisitedDateTime(const QDateTime &lastVisitedDateTime);

    inline int visitCount() const;
    void setVisitCount(int visitCount);

    inline int httpResponseCode() const;
    void setHttpResponseCode(int httpResponseCode);

    inline const QString &httpResponseText() const;
    void setHttpResponseText(const QString &httpResponseText);

    inline const QDateTime &lastCheckDateTime() const;
    void setLastCheckDateTime(const QDateTime &lastCheckDateTime);

    inline bool operator ==(const CBookmark &other);
    inline bool operator !=(const CBookmark &other);
private:
    QSharedDataPointer<CBookmarkData> data;
};

const QUrl &CBookmark::url() const
{
    return data->url;
}

const QString &CBookmark::title() const
{
    return data->title;
}

const QString &CBookmark::description() const
{
    return data->description;
}

const QString &CBookmark::comment() const
{
    return data->comment;
}

const QStringList &CBookmark::keywordList() const
{
    return data->keywordList;
}

bool CBookmark::isReadLater() const
{
    return data->isReadLater;
}

bool CBookmark::isFavorite() const
{
    return data->isFavorite;
}

bool CBookmark::isDeleted() const
{
    return data->isDeleted;
}

int CBookmark::rating() const
{
    return data->rating;
}

const QColor &CBookmark::textColor() const
{
    return data->textColor;
}

const QColor &CBookmark::textBackgroundColor() const
{
    return data->textBackgroundColor;
}

const QDateTime &CBookmark::createdDateTime() const
{
    return data->createdDateTime;
}

const QDateTime &CBookmark::editedDateTime() const
{
    return data->editedDateTime;
}

const QDateTime &CBookmark::lastVisitedDateTime() const
{
    return data->lastVisitedDateTime;
}

int CBookmark::visitCount() const
{
    return data->visitCount;
}

int CBookmark::httpResponseCode() const
{
    return data->httpResponseCode;
}

const QString &CBookmark::httpResponseText() const
{
    return data->httpResponseText;
}

const QDateTime &CBookmark::lastCheckDateTime() const
{
    return data->lastCheckDateTime;
}

bool CBookmark::operator ==(const CBookmark &other)
{
    return (data->title == other.data->title
            && data->url == other.data->url
            && data->description == other.data->description
            && data->comment == other.data->comment
            && data->keywordList == other.data->keywordList
            && data->isReadLater == other.data->isReadLater
            && data->isFavorite == other.data->isFavorite
            && data->isDeleted == other.data->isDeleted
            && data->rating == other.data->rating
            && data->textColor == other.data->textColor
            && data->textBackgroundColor == other.data->textBackgroundColor
            && data->createdDateTime == other.data->createdDateTime
            && data->editedDateTime == other.data->editedDateTime
            && data->lastVisitedDateTime == other.data->lastVisitedDateTime
            && data->visitCount == other.data->visitCount
            && data->httpResponseCode == other.data->httpResponseCode
            && data->httpResponseText == other.data->httpResponseText
            && data->lastCheckDateTime == other.data->lastCheckDateTime);
}

bool CBookmark::operator !=(const CBookmark &other)
{
    return (data->title != other.data->title
            || data->url != other.data->url
            || data->description != other.data->description
            || data->comment != other.data->comment
            || data->keywordList != other.data->keywordList
            || data->isReadLater != other.data->isReadLater
            || data->isFavorite != other.data->isFavorite
            || data->isDeleted != other.data->isDeleted
            || data->rating != other.data->rating
            || data->textColor != other.data->textColor
            || data->textBackgroundColor != other.data->textBackgroundColor
            || data->createdDateTime != other.data->createdDateTime
            || data->editedDateTime != other.data->editedDateTime
            || data->lastVisitedDateTime != other.data->lastVisitedDateTime
            || data->visitCount != other.data->visitCount
            || data->httpResponseCode != other.data->httpResponseCode
            || data->httpResponseText != other.data->httpResponseText
            || data->lastCheckDateTime != other.data->lastCheckDateTime);
}


#endif // CBOOKMARK_H
