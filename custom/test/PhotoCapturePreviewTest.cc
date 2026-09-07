#include "PhotoPreviewCapture.h"
#include <QtQuickTest/quicktest.h>
#include <QtQml/qqml.h>

class PreviewTestSetup : public QObject
{
    Q_OBJECT
public slots:
    void applicationAvailable()
    {
        qmlRegisterType<PhotoPreviewCapture>("QGroundControl.Test", 1, 0, "PhotoPreviewCapture");
    }
};
QUICK_TEST_MAIN_WITH_SETUP(PhotoCapturePreview, PreviewTestSetup)
#include "PhotoCapturePreviewTest.moc"
