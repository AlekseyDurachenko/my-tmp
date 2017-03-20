#ifndef VIDEOPLAYERSTREAM_H
#define VIDEOPLAYERSTREAM_H


#include <QImage>
#include <QObject>
#include <VLCQtCore/AbstractVideoStream.h>
#include <QTime>


class VideoPlayerStream : public QObject, public VlcAbstractVideoStream
{
    Q_OBJECT
public:
    explicit VideoPlayerStream(QObject *parent = 0);
    virtual ~VideoPlayerStream() override final;

    void setMediaPlayer(VlcMediaPlayer *player);
    void unsetMediaPlayer();

    const QImage &currentFrame() const;

signals:
    void frameUpdated();

private:
    virtual unsigned formatCallback(char *chroma,
                                    unsigned *width,
                                    unsigned *height,
                                    unsigned *pitches,
                                    unsigned *lines) override final;
    virtual void formatCleanUpCallback() override final;
    virtual void *lockCallback(void **planes) override final;
    virtual void unlockCallback(void *picture, void *const *planes) override final;
    virtual void displayCallback(void *picture) override final;

private:
    VlcMediaPlayer *m_player;
    QImage m_img;
    QTime time;
};


#endif // VIDEOPLAYERSTREAM_H
