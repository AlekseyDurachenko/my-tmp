#include "videoplayer.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QThread>


VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , m_stream(0)
{    
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::setVideoPlayerStream(VideoPlayerStream *stream)
{
    if (m_stream != stream) {
        m_stream = stream;
        connect(m_stream, SIGNAL(frameUpdated()), this, SLOT(update()), Qt::QueuedConnection);
        update();
    }
}

void VideoPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    static int frameCount = 0;
    static QTime fpsTimer;
    if (fpsTimer.isNull()) {
        fpsTimer.start();
    }

    QPainter painter(this);    
    if (m_stream) {
        // data race is gurantied, it can cause a glitches... but for test is does not matter
        painter.drawImage(0, 0, m_stream->currentFrame());
    }
    else {
        painter.fillRect(rect(), Qt::red);
    }

    frameCount++;
    if (fpsTimer.elapsed() >= 1000) {
        qDebug() << "fps = " << (1000.0 * frameCount) / fpsTimer.elapsed();
        frameCount = 0;
        fpsTimer.restart();
    }

    //update();
}
