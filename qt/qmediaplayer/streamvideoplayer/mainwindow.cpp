#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaPlayer>
#include <QtCore>

class MyProvider : public QIODevice
{
public:
    MyProvider(const QString &fileName, QObject *parent = 0)
        : QIODevice(parent)
    {
        m_file.setFileName(fileName);
    }

    virtual bool open(OpenMode mode) override final
    {
        return m_file.open(mode);
    }

    virtual bool atEnd() const override final
    {
        return false;
    }

    virtual qint64 bytesAvailable() const override final
    {
        return m_file.bytesAvailable();
    }

    virtual qint64 size() const override final
    {
        return m_file.size();
    }

    virtual bool isSequential() const override final
    {
        return m_file.isSequential();
    }

    virtual bool seek(qint64 pos) override final
    {
        return m_file.seek(pos);
    }

protected:
    virtual qint64 readData(char *data, qint64 maxSize) override final
    {
        return m_file.read(data, maxSize);
    }

    virtual qint64 writeData(const char *data, qint64 len) override final
    {
        return m_file.write(data, len);
    }

private:
    QFile m_file;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMediaPlayer *player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
    player->setVideoOutput(ui->widget);
    MyProvider *provider = new MyProvider(QDir::homePath() + "/temp/video/water.mp4", this);
    qDebug() << provider->open(QIODevice::ReadOnly);
    player->setMedia(QMediaContent(), provider);
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}
