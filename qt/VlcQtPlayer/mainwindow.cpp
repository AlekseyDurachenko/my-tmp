#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videoplayer.h"
#include <QDir>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , videoPlayer(0)
    , player(0)
    , listPlayer(0)
    , mediaList(0)
    , media(0)
    , instance(0)
{
    ui->setupUi(this);

    instance = new VlcInstance(VlcCommon::args(), this);
    player = new VlcMediaPlayer(instance);

    VideoPlayerStream *stream = new VideoPlayerStream(this);
    stream->setMediaPlayer(player);

    videoPlayer = new VideoPlayer(this);
    videoPlayer->setVideoPlayerStream(stream);
    setCentralWidget(videoPlayer);

    media = new VlcMedia(QDir::homePath() + QDir::separator() + "/2.mp4", true, instance);
    //player->open(media);

    listPlayer = new VlcMediaListPlayer(player, instance);
    mediaList = new VlcMediaList(instance);
    mediaList->addMedia(media);
    listPlayer->setMediaList(mediaList);
    listPlayer->setPlaybackMode(Vlc::Loop);

    listPlayer->play();

    connect(player, SIGNAL(stopped()), this, SLOT(slotStoped()));
    connect(player, SIGNAL(stateChanged()), this, SLOT(slotStateChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotStoped()
{
    qDebug() << "stoped";
}

void MainWindow::slotStateChanged()
{
    qDebug() << "state changed";

}
