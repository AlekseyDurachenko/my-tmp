#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H


#include "videoplayerstream.h"
#include <QWidget>
#include <QOpenGLWidget>


class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPlayer(QWidget *parent = 0);
    virtual ~VideoPlayer() override final;

    void setVideoPlayerStream(VideoPlayerStream *stream);

protected:
    void paintEvent(QPaintEvent *event);

private:
    VideoPlayerStream *m_stream;
};


#endif // VIDEOPLAYER_H
