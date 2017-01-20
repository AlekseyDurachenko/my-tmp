#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QMediaPlayer *player = new QMediaPlayer(this);

    QGraphicsVideoItem *videoItem1 = new QGraphicsVideoItem;
    videoItem1->setOffset(QPointF(-200, -200));
    videoItem1->setSize(QSizeF(500,500));
    videoItem1->setAspectRatioMode(Qt::IgnoreAspectRatio);
    videoItem1->setTransform(QTransform().translate(500, 200).rotate(3).translate(-500, -500));
    player->setVideoOutput(videoItem1);

    player->setMedia(QUrl("file:///home/user/1.mp4"));
    player->play();

    scene->addItem(videoItem1);
    scene->addRect(-200.0, -200.0, 250, 250, QPen(Qt::blue), QBrush(Qt::blue));
}

MainWindow::~MainWindow()
{
    delete ui;
}
