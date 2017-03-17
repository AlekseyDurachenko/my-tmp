#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H


#include "videowidgetsurface.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QMediaPlayer>
#include <QTime>


class VideoWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = 0);
    virtual ~VideoWidget() override final;

private slots:
    void mediaStateChanged(QMediaPlayer::State state);

protected:
    void paintEvent(QPaintEvent *event);

private:
    VideoWidgetSurface *m_surface;
    QMediaPlayer *m_mediaPlayer;
    QImage m_cache;
};


#endif // VIDEOWIDGET_H
