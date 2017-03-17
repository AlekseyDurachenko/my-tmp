/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "videowidgetsurface.h"
#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>


VideoWidgetSurface::VideoWidgetSurface(QObject *parent)
    : QAbstractVideoSurface(parent)
    , imageFormat(QImage::Format_Invalid)
{
}


QList<QVideoFrame::PixelFormat> VideoWidgetSurface::supportedPixelFormats(
    QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
               << QVideoFrame::Format_RGB32
               << QVideoFrame::Format_ARGB32
               << QVideoFrame::Format_ARGB32_Premultiplied
               << QVideoFrame::Format_RGB565
               << QVideoFrame::Format_RGB555;
    }
    else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool VideoWidgetSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
           && !size.isEmpty()
           && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool VideoWidgetSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
        this->imageFormat = imageFormat;
        imageSize = size;
        sourceRect = format.viewport();

        QAbstractVideoSurface::start(format);

        return true;
    }
    else {
        return false;
    }
}

void VideoWidgetSurface::stop()
{
    currentFrame = QVideoFrame();
    targetRect = QRect();

    QAbstractVideoSurface::stop();
}

bool VideoWidgetSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
            || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();
        qDebug() << "error";

        return false;
    }
    else {
        currentFrame = frame;
        return true;
    }
}

QImage VideoWidgetSurface::cache()
{
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        return QImage(currentFrame.bits(),
                      currentFrame.width(),
                      currentFrame.height(),
                      currentFrame.bytesPerLine(),
                      imageFormat).copy();
        currentFrame.unmap();
    }

    return QImage();
}
