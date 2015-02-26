#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cbookmarkmgr.h"
#include <QDebug>
#include "bookmarkimportchromium.h"
#include <QDir>


void printTagItem(const QString &path, CTagItem *item)
{
    foreach (CTagItem *tmp, item->children())
    {
        qDebug() << path + tmp->data().name();
        printTagItem(path + tmp->data().name() + " >> ", tmp);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CBookmarkMgr *bookmarkMgr = new CBookmarkMgr(this);
//    CBookmark _b1;
//    _b1.setUrl(QUrl("ru.ru"));
//    CBookmarkItem *b1 = bookmarkMgr->bookmarkAdd(_b1);

//    CTag _t1;
//    _t1.setName("unnamed");
//    CTagItem *t1 = bookmarkMgr->tagRootItem()->addChild(_t1);

//    t1->bookmarkAdd(b1);
//    t1->bookmarkAdd(b1);
    bookmarkImportChromium(bookmarkMgr, QDir::homePath() + "/.config/chromium/Default/Bookmarks");


    foreach (CBookmarkItem *item, bookmarkMgr->bookmarks())
    {
        qDebug() << item->data().url();
        foreach (CTagItem *tag, item->tags())
            qDebug() << "TAG: " << tag->path();
    }

    printTagItem("", bookmarkMgr->tagRootItem());

    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
