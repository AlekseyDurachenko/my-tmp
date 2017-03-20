#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "videoplayer.h"
#include <QMainWindow>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaListPlayer.h>
#include <VLCQtCore/MediaList.h>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow() override final;

private slots:
    void slotStoped();
    void slotStateChanged();

private:
    Ui::MainWindow *ui;
    VideoPlayer *videoPlayer;
    VlcMediaPlayer *player;
    VlcMediaListPlayer *listPlayer;
    VlcMediaList *mediaList;
    VlcMedia *media;
    VlcInstance *instance;
};


#endif // MAINWINDOW_H
