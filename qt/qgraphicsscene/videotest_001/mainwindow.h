#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QMediaPlayer>
#include "mygraphicsvideoitem.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_imgRotate_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QMediaPlayer *m_player_1;
    QMediaPlayer *m_player_2;
    QGraphicsVideoItem *m_video_item_1;
    MyGraphicsVideoItem *m_video_item_2;
};


#endif // MAINWINDOW_H
