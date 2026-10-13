/****************************************************************************
 *
 * (c) 2025 Custom VOXL GCS
 *
 ****************************************************************************/

#pragma once

#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QTimer>
#ifdef Q_OS_ANDROID
#include <QtCore/QJniObject>
#endif

#include "LinkInterface.h"
#include "PhotoCaptureFeedback.h"

class MavlinkCameraControl;
#include "QVIOHandler.h"
#include "ToFHandler.h"
#include "Vehicle.h"
#include "Video/VideoHandler.h"

class CustomQGCApplication : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PhotoCaptureFeedback *photoFeedback READ photoFeedback CONSTANT)
    Q_PROPERTY(double vioQuality READ vioQuality NOTIFY vioChanged)
    Q_PROPERTY(QString vioStatus READ vioStatus NOTIFY vioChanged)
    Q_PROPERTY(QVIOHandler *qvioHandler READ qvioHandler CONSTANT)
    Q_PROPERTY(ToFHandler *tofHandler READ tofHandler CONSTANT)
    Q_PROPERTY(VideoHandler *videoHandler READ videoHandler CONSTANT)
    Q_PROPERTY(QString statusOverlayMessage READ statusOverlayMessage NOTIFY statusOverlayChanged)
    Q_PROPERTY(bool statusOverlayVisible READ statusOverlayVisible NOTIFY statusOverlayChanged)
    Q_PROPERTY(bool returnToHomeEnabled READ returnToHomeEnabled WRITE setReturnToHomeEnabled NOTIFY returnToHomeEnabledChanged)

public:
    explicit CustomQGCApplication(QObject *parent = nullptr);
    ~CustomQGCApplication() override;
    Q_INVOKABLE void playShutterSound();

    PhotoCaptureFeedback *photoFeedback() { return &_photoFeedback; }
    Q_INVOKABLE bool takePhoto(MavlinkCameraControl *camera);

    double vioQuality() const { return _qvioHandler.quality(); }
    QString vioStatus() const { return _qvioHandler.stateLabel(); }
    QVIOHandler *qvioHandler() { return &_qvioHandler; }
    ToFHandler *tofHandler() { return &_tofHandler; }
    VideoHandler *videoHandler() const { return _videoHandler; }
    QString statusOverlayMessage() const { return _statusOverlayMessage; }
    static QString statusSpeechText(const QString &text);
    static QString statusMessageKey(const QString &text);
    bool statusOverlayVisible() const { return !_statusOverlayMessage.isEmpty(); }
    // UI only for now: not yet sent to voxl-vision-hub
    bool returnToHomeEnabled() const { return _returnToHomeEnabled; }
    void setReturnToHomeEnabled(bool enabled);

public slots:
    void recordStart();
    void recordStop();
    void snapshot();
    void swapCamera();

signals:
    void vioChanged();
    void statusOverlayChanged();
    void returnToHomeEnabledChanged();

private slots:
    void _activeVehicleChanged(Vehicle *vehicle);
    void _handleMavlinkMessage(const mavlink_message_t &message);
    void _handleTextMessage(int sysid, int componentid, int severity, QString text, QString description);
    void _loadSavedUrls();
    void _persistUrls();
    void _bindVideoSettings();
    void _handleTransientStatusOverlayTimeout();

private:
    static bool _parseStatusOverlayMessage(const QString &text, QString &displayMessage, bool &persistent, QString &messageKey);
    static QString _translatedStatusText(const QString &code, QChar level, int genre);
    void _setStatusOverlayMessage(const QString &message);
    void _clearStatusOverlay();

    PhotoCaptureFeedback _photoFeedback;
#ifdef Q_OS_ANDROID
    QJniObject _shutterSound;
#endif
    Vehicle *_vehicle = nullptr;
    VideoHandler *_videoHandler = nullptr;
    QVIOHandler _qvioHandler;
    ToFHandler _tofHandler;
    QSettings _settings;
    QString _statusOverlayMessage;
    QString _persistentStatusOverlayMessage;
    QString _persistentStatusOverlayKey;
    QTimer _statusOverlayTimer;
    bool _returnToHomeEnabled = true;
};
