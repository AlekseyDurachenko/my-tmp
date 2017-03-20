#include "videoplayerstream.h"
#include <QDebug>
#include <QTime>


VideoPlayerStream::VideoPlayerStream(QObject *parent)
    : QObject(parent)
    , m_player(0)
{
    m_img = QImage(10, 10, QImage::Format_RGB32);
    m_img.fill(Qt::black);
}

VideoPlayerStream::~VideoPlayerStream()
{
    unsetMediaPlayer();
}

void VideoPlayerStream::setMediaPlayer(VlcMediaPlayer *player)
{
    if (m_player != player) {
        m_player = player;
        setCallbacks(m_player);
    }
}

void VideoPlayerStream::unsetMediaPlayer()
{
    if (m_player) {
        unsetCallbacks(m_player);
        m_player = 0;
    }
}

const QImage &VideoPlayerStream::currentFrame() const
{
    return m_img;
}

unsigned VideoPlayerStream::formatCallback(char *chroma,
                                           unsigned *width,
                                           unsigned *height,
                                           unsigned *pitches,
                                           unsigned *lines)
{
    if (*width > 0 && *height > 0) {
        m_img = QImage(*width, *height, QImage::Format_RGB32);
        qstrcpy(chroma, "RV32");
        *pitches = *width * 4; // hack: why * 4???
        *lines = *height;

        return 3; // hack: why 3???
    }
    else {
        qDebug() << "VideoPlayerStream::formatCallback() width or height are zero";
    }

    return -1; // LCOV_EXCL_LINE
}

void VideoPlayerStream::formatCleanUpCallback()
{
    emit frameUpdated();
}

void *VideoPlayerStream::lockCallback(void **planes)
{
    time.restart();
    planes[0] = m_img.bits();

    return reinterpret_cast<void *>(1);
}

void VideoPlayerStream::unlockCallback(void *picture, void * const *planes)
{
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    qDebug() << "frame created in " << time.elapsed();
}

void VideoPlayerStream::displayCallback(void *picture)
{
    Q_UNUSED(picture);
    emit frameUpdated();
}
