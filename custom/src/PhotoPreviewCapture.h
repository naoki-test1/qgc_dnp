#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

class QQuickItem;

class PhotoPreviewCapture : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;
    Q_INVOKABLE QString capture(QQuickItem *videoSurface) const;
};
