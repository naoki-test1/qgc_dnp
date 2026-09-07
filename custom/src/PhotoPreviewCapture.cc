#include "PhotoPreviewCapture.h"

#include <QtCore/QBuffer>
#include <QtQuick/QQuickItem>
#include <QtQuick/QQuickWindow>

QString PhotoPreviewCapture::capture(QQuickItem *videoSurface) const
{
    if (!videoSurface || !videoSurface->window() || !videoSurface->isVisible()) {
        return QString();
    }
    QQuickWindow *window = videoSurface->window();
    if (!window->isVisible() || window->width() <= 0 || window->height() <= 0) {
        return QString();
    }
    // Never grabToImage() the GStreamer item: its offscreen render pass can
    // replace the live sink's scene-graph resources. Copy the normal window instead.
    const QImage frame = window->grabWindow();
    if (frame.isNull()) {
        return QString();
    }
    const QRectF sceneRect = videoSurface->mapRectToScene(videoSurface->boundingRect());
    const qreal scaleX = qreal(frame.width()) / window->width();
    const qreal scaleY = qreal(frame.height()) / window->height();
    const QRect crop = QRectF(sceneRect.x() * scaleX, sceneRect.y() * scaleY,
                             sceneRect.width() * scaleX, sceneRect.height() * scaleY)
                           .toAlignedRect().intersected(frame.rect());
    if (crop.isEmpty()) {
        return QString();
    }
    const QImage thumbnail = frame.copy(crop).scaled(480, 270, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    if (!thumbnail.save(&buffer, "PNG")) {
        return QString();
    }
    return QStringLiteral("data:image/png;base64,") + QString::fromLatin1(bytes.toBase64());
}
