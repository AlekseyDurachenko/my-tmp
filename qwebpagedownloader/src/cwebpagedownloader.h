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
#ifndef CWEBPAGEDOWNLOADER_H
#define CWEBPAGEDOWNLOADER_H

#include <QObject>
#include <QList>
#include <QWebPage>
#include "cwebfiledownloader.h"


class CWebPageDownloader : public QObject
{
    Q_OBJECT
public:
    explicit CWebPageDownloader(QNetworkAccessManager *network, QObject *parent = 0);
    virtual ~CWebPageDownloader();

    inline const QUrl &url() const;
    void setUrl(const QUrl &url);

    inline const QString &fileName() const;
    inline const QString &resourcesPath() const;
    void setFileName(const QString& fileName);

    void start();
    void abort();
    inline bool isStarted() const;
    inline bool isAborted() const;
    inline bool isFinished() const;
signals:
    void downloadProgress(qint64 total, qint64 count);
    void finished();
public slots:
    void pagedownloader_finished();
    void resdownloader_finished();
    void webpage_loadFinished();
private:
    void processPage(const QByteArray &data);
private:
    QNetworkAccessManager *m_network;
    CWebFileDownloader *m_pageDownloader;
    QList<CWebFileDownloader *> m_resDownloaders;
    QUrl m_url;
    QString m_fileName;
    QString m_resourcesPath;
    bool m_isAborted;
    bool m_isStarted;
    bool m_isFinished;
    QWebPage *m_webPage;
    int m_fileId;
};

const QUrl &CWebPageDownloader::url() const
{
    return m_url;
}

const QString &CWebPageDownloader::fileName() const
{
    return m_fileName;
}

const QString &CWebPageDownloader::resourcesPath() const
{
    return m_resourcesPath;
}

bool CWebPageDownloader::isStarted() const
{
    return m_isStarted;
}

bool CWebPageDownloader::isAborted() const
{
    return m_isAborted;
}

bool CWebPageDownloader::isFinished() const
{
    return m_isFinished;
}


#endif // CWEBPAGEDOWNLOADER_H
