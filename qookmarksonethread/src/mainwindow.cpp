#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include "cmanager.h"
#include "ctagmgr.h"
#include "ctagitem.h"
#include "cbookmarkmgr.h"
#include "cbookmarkitem.h"
#include "bookmarkimportchromium.h"
#include "ctagitemmodel.h"
#include "cbookmarkfilter.h"
#include "cbookmarkfilterdatamodel.h"
#include "cbookmarkfilter.h"
#include "cbookmarkfilteritemmodel.h"

void printTagItem(const QString &path, CTagItem *item)
{
    foreach (CTagItem *tmp, item->children())
    {
        qDebug() << path + tmp->data().name() << "(" << tmp->bookmarks().count() << ")";
        printTagItem(path + tmp->data().name() + " >> ", tmp);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QSet<QString> set;
//    set << "January" << "February" << "December";

//    foreach (QString item, set)
//    {
//        qDebug() << set;
//        qDebug() << item;
//        set.remove(item);
//    }
//    qDebug() << set;


//    QSet<QString> set;
//    set << "January" << "February" << "December";

//    QSet<QString>::iterator i;
//    for (i = set.begin(); i != set.end(); i = set.erase(i))
//    {
//        qDebug() << set;
//        qDebug() << *i;
//    }
//    qDebug() << set;

//    QSet<QString>::iterator i = set.begin();
//    while (i != set.end()) {
//        qDebug() << *i;
//        i = set.erase(i);
//    }

//    qDebug() << set;
//    exit(0);

//    CBookmarkMgr *bookmarkMgr = new CBookmarkMgr(this);
//    CBookmark _b1;
//    _b1.setUrl(QUrl("ru.ru"));
//    CBookmarkItem *b1 = bookmarkMgr->bookmarkAdd(_b1);

//    CTag _t1;
//    _t1.setName("unnamed");
//    CTagItem *t1 = bookmarkMgr->tagRootItem()->addChild(_t1);

//    t1->bookmarkAdd(b1);
//    t1->bookmarkAdd(b1);
    //bookmarkImportChromium(bookmarkMgr, QDir::homePath() + "/.config/chromium/Default/Bookmarks");


//    foreach (CBookmarkItem *item, bookmarkMgr->bookmarks())
//    {
//        qDebug() << item->data().url();
//        foreach (CTagItem *tag, item->tags())
//            qDebug() << "TAG: " << tag->path();
//    }

//    printTagItem("", bookmarkMgr->tagRootItem());

    //CTagItemModel *model = new CTagItemModel(bookmarkMgr->tagRootItem(), this);
    //ui->tag_treeView->setModel(model);

    mgr = new CManager(this);
    dataModel = new CBookmarkFilterDataModel(mgr->bookmarkMgr(), this);
    filter = new CBookmarkFilter(mgr->tagMgr(), this);
    dataModel->setFilter(filter);
    CBookmarkFilteredItemModel *model = new CBookmarkFilteredItemModel(dataModel, this);
    ui->treeView_bookmarks->setModel(model);


    bookmarkImportChromium(mgr, QDir::homePath() + "/.config/chromium/Default/Bookmarks");



    foreach (CBookmarkItem *item, mgr->bookmarkMgr()->bookmarks())
    {
        qDebug() << item->data().url();
        foreach (CTagItem *tag, item->tags())
            qDebug() << "TAG: " << tag->path();
    }

    printTagItem("", mgr->tagMgr()->rootItem());

    CBookmark data = mgr->bookmarkMgr()->at(0)->data();
    data.setTrash(true);
    mgr->bookmarkMgr()->at(0)->setData(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    filter->setInclusiveOption(Bookmark::FilterOptions(Bookmark::Trash));
    filter->update();
}

void MainWindow::on_action_Save_triggered()
{
    CBookmark data = mgr->bookmarkMgr()->at(1)->data();
    data.setTrash(true);
    mgr->bookmarkMgr()->at(1)->setData(data);
}
