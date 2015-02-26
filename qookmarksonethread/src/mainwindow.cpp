#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "cbookmarkmgr.h"
#include <QStack>
#include <QStringList>

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
    CTag tag1;
    tag1.setName("name_1");
    CTag tag2;
    tag2.setName("name_2");
    CTag tag3;
    tag3.setName("name_3");
    CTag tag4;
    tag4.setName("name_4");
    CTagItem *t1 = bookmarkMgr->tagRootItem()->addChild(tag1);
    CTagItem *t2 = bookmarkMgr->tagRootItem()->addChild(tag2)->addChild(tag3);
    CTagItem *t3 = bookmarkMgr->tagRootItem()->addChild(tag4);


    CBookmark b1;
    b1.setUrl(QUrl("a1.ru"));
    CBookmark b2;
    b2.setUrl(QUrl("a2.ru"));
    CBookmark b3;
    b3.setUrl(QUrl("a3.ru"));
    bookmarkMgr->bookmarkAdd(b1);
    bookmarkMgr->bookmarkAdd(b2);
    bookmarkMgr->bookmarkAdd(b3);

    t1->bookmarkAdd(bookmarkMgr->bookmarkAt(0));
    t2->bookmarkAdd(bookmarkMgr->bookmarkAt(0));
    t3->bookmarkAdd(bookmarkMgr->bookmarkAt(0));

    foreach (CBookmarkItem *item, bookmarkMgr->bookmarks())
    {
        qDebug() << item->data().url();
        foreach (CTagItem *tag, item->tags())
            qDebug() << "TAG: " << tag->data().name();
    }

    printTagItem("", bookmarkMgr->tagRootItem());

    exit(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
