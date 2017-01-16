#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cbookmark.h"
#include <QDebug>
#include "ccorefacade.h"
#include "cbookmarkitemmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CCoreFacade *facade = new CCoreFacade(this);
    CBookmarkRepresentation *bookmarkRep = facade->bookmarkRepresentation();
    CBookmarkItemModel *model = new CBookmarkItemModel(bookmarkRep, this);
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
