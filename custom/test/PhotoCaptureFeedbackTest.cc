#include "PhotoCaptureFeedback.h"
#include <QtTest/QTest>

class PhotoCaptureFeedbackTest : public QObject
{
    Q_OBJECT
private slots:
    void successfulCapture()
    {
        PhotoCaptureFeedback feedback;
        QVERIFY(feedback.begin(1, 100));
        QCOMPARE(feedback.state(), "saving");
        QVERIFY(!feedback.begin(1, 100));
        feedback.imageCaptured(1, 100, 0, 1000, 1);
        QCOMPARE(feedback.state(), "saved");
        for (auto timer : feedback.findChildren<QTimer *>()) {
            if (timer->isActive()) {
                QCOMPARE(timer->interval(), 2000);
                QMetaObject::invokeMethod(timer, "timeout");
            }
        }
        QCOMPARE(feedback.state(), "idle");
    }
    void onlySelectedCameraCanComplete()
    {
        PhotoCaptureFeedback feedback;
        feedback.begin(1, 100);
        feedback.imageCaptured(2, 100, 1, 1000, 1);
        feedback.imageCaptured(1, 101, 1, 1000, 1);
        feedback.commandRejected(2, 100);
        feedback.commandRejected(1, 101);
        feedback.imageCaptured(1, 100, 1, 1000, 2);
        QCOMPARE(feedback.state(), "saving");
        feedback.imageCaptured(1, 100, 1, 1000, 0);
        QCOMPARE(feedback.state(), "failed");
    }
    void oldResultsCannotConfirmNextCapture()
    {
        PhotoCaptureFeedback feedback;
        feedback.imageCaptured(1, 100, 5, 1000, 1);
        feedback.begin(1, 100);
        feedback.imageCaptured(1, 100, 5, 1000, 1);
        feedback.imageCaptured(1, 100, 4, 900, 1);
        QCOMPARE(feedback.state(), "saving");
        feedback.imageCaptured(1, 100, 6, 1100, 1);
        QCOMPARE(feedback.state(), "saved");
    }
    void rejectionAndTimeout()
    {
        PhotoCaptureFeedback feedback;
        feedback.begin(1, 100);
        feedback.commandRejected(1, 100);
        QCOMPARE(feedback.state(), "failed");
        feedback.begin(1, 100);
        for (auto timer : feedback.findChildren<QTimer *>()) {
            if (timer->isActive()) {
                QCOMPARE(timer->interval(), 15000);
                QMetaObject::invokeMethod(timer, "timeout");
                break;
            }
        }
        QCOMPARE(feedback.state(), "unconfirmed");
        feedback.imageCaptured(1, 100, 1, 1000, 1);
        QCOMPARE(feedback.state(), "unconfirmed");
    }
    void switchingCameraOrVehicleClearsPending()
    {
        PhotoCaptureFeedback feedback;
        feedback.begin(1, 100);
        feedback.clear();
        feedback.imageCaptured(1, 100, 1, 1000, 1);
        QCOMPARE(feedback.state(), "idle");
        feedback.reset();
        feedback.begin(1, 100);
        feedback.imageCaptured(1, 100, 0, 10, 1);
        QCOMPARE(feedback.state(), "saved");
    }
};
QTEST_GUILESS_MAIN(PhotoCaptureFeedbackTest)
#include "PhotoCaptureFeedbackTest.moc"
