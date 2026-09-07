#pragma once

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QTimer>

// Tracks one user capture at a time. A command ACK is never proof of a saved image.
class PhotoCaptureFeedback : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
public:
    explicit PhotoCaptureFeedback(QObject *parent = nullptr);
    QString state() const { return _state; }
    bool begin(int systemId, int componentId);
    void imageCaptured(int systemId, int componentId, int imageIndex, quint32 bootTime, int result);
    void commandRejected(int systemId, int componentId);
    Q_INVOKABLE void clear();
    void reset();
signals:
    void stateChanged();
private:
    void _finish(const QString &state);
    void _setState(const QString &state);
    struct Image { int index = -1; quint32 bootTime = 0; };
    QHash<int, Image> _lastImages;
    Image _baseline;
    QString _state = QStringLiteral("idle");
    int _systemId = -1;
    int _componentId = -1;
    QTimer _timeout;
    QTimer _dismiss;
};
