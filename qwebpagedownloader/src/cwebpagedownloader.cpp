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
#include "cwebpagedownloader.h"
#include <QDir>
#include <QDebug>
#include <QStack>
#include <QWebElement>
#include <QtWebKit>
#include <QWebFrame>


CWebPageDownloader::CWebPageDownloader(QNetworkAccessManager *network,
        QObject *parent) : QObject(parent)
{
    m_network = network;
    m_pageDownloader = 0;
    m_webPage = 0;
    m_isAborted = false;
    m_isStarted = false;
    m_isFinished = false;
    m_fileId = 0;
}

CWebPageDownloader::~CWebPageDownloader()
{
    delete m_pageDownloader;
}

void CWebPageDownloader::setUrl(const QUrl &url)
{
    m_url = url;
}

void CWebPageDownloader::setFileName(const QString &fileName)
{
    m_fileName = fileName;
    m_resourcesPath = fileName + ".res";
}

void CWebPageDownloader::start()
{
    if (isStarted())
        return;

    m_isStarted = true;
    m_isAborted = false;
    m_isFinished = false;
    m_resDownloaders.clear();
    m_fileId = 0;

    QDir().mkpath(resourcesPath());

    m_pageDownloader = new CWebFileDownloader(m_network, this);
    m_pageDownloader->setFileName(QString());
    m_pageDownloader->setUrl(m_url);
    m_pageDownloader->setSaveBuffer(true);
    connect(m_pageDownloader, SIGNAL(finished()),
            this, SLOT(pagedownloader_finished()));
    m_pageDownloader->start();
}

void CWebPageDownloader::abort()
{
}

void CWebPageDownloader::pagedownloader_finished()
{
    processPage(m_pageDownloader->buffer());

    m_pageDownloader->deleteLater();
    m_pageDownloader = 0;
}

void CWebPageDownloader::resdownloader_finished()
{
}

void CWebPageDownloader::webpage_loadFinished()
{
    bool hasCodepage = false;
    QWebFrame *frame = m_webPage->mainFrame();
    QWebElement e = frame->documentElement();
    QStack<QWebElement> stack;
    while (!e.isNull() || !stack.isEmpty())
    {
        if (e.isNull())
        {
            e = stack.pop();

//            if (e.tagName().toLower() == "head" && !hasCodepage)
//            {
//                qDebug() << "meta!!!!!";
//                QWebElement elem;
//                elem.appendInside("<meta/>");
//                //e.appendInside(elem);
//                //e.prependOutside("meta");
//                e.appendInside(elem.lastChild());
//            }

            //qDebug() << QString().fill(' ', stack.count()) + "/" + e.tagName();
            e = e.nextSibling();
        }
        else
        {
            //qDebug() << QString().fill(' ', stack.count()) + e.tagName();
            if (e.tagName().toLower() == "link"
                    && e.attribute("rel").toLower() == "stylesheet")
            {
                QString href = e.attribute("href");
                QUrl url = m_url.resolved(QUrl(href));
                QString baseFileName = QString::number(++m_fileId) + ".css";
                QString fileName = m_resourcesPath + QDir::separator() + baseFileName;
                e.setAttribute("href", QFileInfo(m_resourcesPath).fileName() + QDir::separator() + baseFileName);

                CWebFileDownloader *downloader = new CWebFileDownloader(m_network, this);
                downloader->setFileName(fileName);
                downloader->setUrl(url);
                connect(downloader, SIGNAL(finished()),
                        downloader, SLOT(deleteLater()));
                downloader->start();
            }
            else if (e.tagName().toLower() == "script")
            {
                QString href = e.attribute("src");

                QUrl url = m_url.resolved(QUrl(href));
                QString baseFileName = QString::number(++m_fileId) + ".js";
                QString fileName = m_resourcesPath + QDir::separator() + baseFileName;
                e.setAttribute("src", QFileInfo(m_resourcesPath).fileName() + QDir::separator() + baseFileName);

                CWebFileDownloader *downloader = new CWebFileDownloader(m_network, this);
                downloader->setFileName(fileName);
                downloader->setUrl(url);
                connect(downloader, SIGNAL(finished()),
                        downloader, SLOT(deleteLater()));
                downloader->start();
            }
            else if (e.tagName().toLower() == "img")
            {
                QString href = e.attribute("src");

                QUrl url = m_url.resolved(QUrl(href));
                QString baseFileName = QString::number(++m_fileId) + ".img";
                QString fileName = m_resourcesPath + QDir::separator() + baseFileName;
                e.setAttribute("src", QFileInfo(m_resourcesPath).fileName() + QDir::separator() + baseFileName);

                CWebFileDownloader *downloader = new CWebFileDownloader(m_network, this);
                downloader->setFileName(fileName);
                downloader->setUrl(url);
                connect(downloader, SIGNAL(finished()),
                        downloader, SLOT(deleteLater()));
                downloader->start();

                qDebug() << url;
            }
            else if (e.tagName().toLower() == "meta"
                    && e.attribute("http-equiv").toLower() == "content-type")
            {
                e.setAttribute("content", "text/html; charset=utf-8");
                hasCodepage = true;
            }

            stack.push(e);
            e = e.firstChild();
        }
    }

    if (!hasCodepage)
    {
        QWebElement elem = frame->findFirstElement("head");
        elem.setInnerXml("<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />" + elem.toInnerXml());
    }

    QFile outputFile(m_fileName);
    outputFile.open(QIODevice::WriteOnly);
    outputFile.write(frame->toHtml().toUtf8());
    //qDebug() << frame->toHtml();
}

void CWebPageDownloader::processPage(const QByteArray &data)
{
    m_webPage = new QWebPage(this);
    QWebFrame *frame = m_webPage->mainFrame();
    connect(frame, SIGNAL(loadFinished(bool)),
            this, SLOT(webpage_loadFinished()));
    //frame->setContent(data, "text/html; charset=windows-1251", m_url);
    //frame->setHtml(QString::fromUtf8(data));
    frame->setUrl(m_url);
    //frame->setContent(data);
}
