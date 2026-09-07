#include "PhotoCaptureFeedback.h"

PhotoCaptureFeedback::PhotoCaptureFeedback(QObject *parent)
    : QObject(parent), _timeout(this), _dismiss(this)
{
    _timeout.setSingleShot(true);
    _timeout.setInterval(15000);
    _dismiss.setSingleShot(true);
    connect(&_timeout, &QTimer::timeout, this, [this]() { _finish(QStringLiteral("unconfirmed")); });
    connect(&_dismiss, &QTimer::timeout, this, &PhotoCaptureFeedback::clear);
}

bool PhotoCaptureFeedback::begin(int systemId, int componentId)
{
    if (_state == QStringLiteral("saving")) {
        return false;
    }
    _dismiss.stop();
    _systemId = systemId;
    _componentId = componentId;
    _baseline = _lastImages.value((systemId << 8) | componentId);
    _timeout.start();
    _setState(QStringLiteral("saving"));
    return true;
}

void PhotoCaptureFeedback::imageCaptured(int systemId, int componentId, int imageIndex, quint32 bootTime, int result)
{
    if (result != 0 && result != 1) {
        return;
    }
    const int key = (systemId << 8) | componentId;
    const auto previous = _lastImages.value(key);
    // Repeated/replayed notifications must not complete a subsequent capture.
    if (previous.index >= 0 && imageIndex <= previous.index
        && (bootTime == 0 || previous.bootTime == 0 || static_cast<qint32>(bootTime - previous.bootTime) <= 0)) {
        return;
    }
    _lastImages.insert(key, {imageIndex, bootTime});
    if (_state != QStringLiteral("saving") || systemId != _systemId || componentId != _componentId) {
        return;
    }
    if (_baseline.index >= 0 && imageIndex <= _baseline.index
        && (bootTime == 0 || _baseline.bootTime == 0 || static_cast<qint32>(bootTime - _baseline.bootTime) <= 0)) {
        return;
    }
    _finish(result == 1 ? QStringLiteral("saved") : QStringLiteral("failed"));
}

void PhotoCaptureFeedback::commandRejected(int systemId, int componentId)
{
    if (_state == QStringLiteral("saving") && systemId == _systemId && componentId == _componentId) {
        _finish(QStringLiteral("failed"));
    }
}

void PhotoCaptureFeedback::_finish(const QString &state)
{
    if (_state != QStringLiteral("saving")) {
        return;
    }
    _timeout.stop();
    _dismiss.start(state == QStringLiteral("saved") ? 2000 : 5000);
    _setState(state);
}

void PhotoCaptureFeedback::clear()
{
    _timeout.stop();
    _dismiss.stop();
    _setState(QStringLiteral("idle"));
}

void PhotoCaptureFeedback::reset()
{
    clear();
    _lastImages.clear();
}

void PhotoCaptureFeedback::_setState(const QString &state)
{
    if (_state != state) {
        _state = state;
        emit stateChanged();
    }
}
