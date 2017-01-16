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
#include <QApplication>
#include <QTextCodec>
#include "cwebfiledownloader.h"
#include "cwebpagedownloader.h"
#include "cwebpagescreenshot.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QNetworkAccessManager *network = new QNetworkAccessManager;
    CWebPageScreenshot screenshot(network);
    screenshot.setUrl(QUrl("http://sourceforge.net/p/cutycapt/code/HEAD/tree/CutyCapt/CutyCapt.cpp"));
    screenshot.setScreenshotSize(QSize(1280, 800));
    screenshot.start();
    return app.exec();

    CWebPageDownloader downloader(network, 0);
    //downloader.setUrl(app.arguments().at(1));
    //downloader.setFileName(app.arguments().at(2));
    downloader.setUrl(QUrl("http://habrahabr.ru/post/198142/"));
    //downloader.setUrl(QUrl("http://www.cse.msu.edu/~chooseun/Test2.pdf"));
    //downloader.setUrl(QUrl("http://virink.com/post/133968"));
    //downloader.setUrl(QUrl("http://zhurnal.lib.ru/j/jagun_ewgenij/replikanjachuksinu.shtml"));
    downloader.setFileName("/tmp/img.html");
    downloader.start();

    QObject::connect(&downloader, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}
