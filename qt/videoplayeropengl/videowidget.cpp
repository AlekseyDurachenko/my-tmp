#include "videowidget.h"
#include "videowidgetsurface.h"
#include <QtWidgets>
#include <qvideosurfaceformat.h>


VideoWidget::VideoWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_surface(0)
{
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground, true);

    m_cache = QImage(100, 100, QImage::Format_ARGB32);
    m_cache.fill(0);

    m_surface = new VideoWidgetSurface(0);

    m_mediaPlayer = new QMediaPlayer(this);
    connect(m_mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    m_mediaPlayer->setVideoOutput(m_surface);
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::homePath() + QDir::separator() + "/temp/video/2.mp4"));
    m_mediaPlayer->setVolume(0.0);
    m_mediaPlayer->play();
}

VideoWidget::~VideoWidget()
{
    delete m_surface;
}

void VideoWidget::mediaStateChanged(QMediaPlayer::State state)
{
    qDebug() << "current state" << state;
    if (state == QMediaPlayer::StoppedState) {
        m_mediaPlayer->setPosition(0);
        m_mediaPlayer->play();
    }
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    static int frameCount = 0;
    static QTime fpsTimer;
    if (fpsTimer.isNull()) {
        fpsTimer.start();
    }



    QPainter painter(this);
    if (m_surface->isActive()) {
        m_cache = m_surface->cache();
    }
    painter.drawImage(rect(), m_cache, m_cache.rect());
    update();



    frameCount++;
    if (fpsTimer.elapsed() >= 1000) {
        qDebug() << "fps = " << (1000.0 * frameCount) / fpsTimer.elapsed();
        frameCount = 0;
        fpsTimer.restart();
    }
}
