import QtQuick
import QtTest
import QGroundControl.Test 1.0
import "../../qml" as Custom

TestCase {
    id: testCase
    name: "PhotoCapturePreview"
    when: windowShown
    visible: true
    width: 800
    height: 480
    QtObject { id: fakeFeedback; property string state: "idle" }
    Rectangle { id: video; width: 640; height: 360; color: "steelblue" }
    PhotoPreviewCapture { id: capture }
    Custom.PhotoCapturePreview {
        frameCapture: capture
        id: preview
        feedback: fakeFeedback
        videoSurface: video
        streaming: true
    }
    function init() { fakeFeedback.state = "idle"; preview.streaming = true; video.color = "steelblue" }
    function cleanup() { fakeFeedback.state = "idle" }
    function test_thumbnailAndSuccess() {
        preview.prepareThumbnail()
        fakeFeedback.state = "saving"
        verify(preview.visible)
        verify(preview.layer.enabled)
        verify(preview.clip)
        tryVerify(function() { return preview.thumbnailSource.toString().length > 0 })
        fakeFeedback.state = "saved"
        compare(preview.captureState, "saved")
        verify(preview.visible)
        fakeFeedback.state = "idle"
        verify(!preview.visible)
        verify(!preview.layer.enabled)
        compare(preview.thumbnailSource.toString(), "")
    }
    function test_noVideoAndFailure() {
        preview.streaming = false
        preview.prepareThumbnail()
        fakeFeedback.state = "saving"
        compare(preview.thumbnailSource.toString(), "")
        verify(preview.visible)
        fakeFeedback.state = "failed"
        compare(preview.captureState, "failed")
        fakeFeedback.state = "unconfirmed"
        compare(preview.captureState, "unconfirmed")
    }
    function test_liveSurfaceKeepsUpdating() {
        const originalParent = video.parent
        const originalWidth = video.width
        preview.prepareThumbnail()
        const firstFrame = preview.thumbnailSource.toString()
        verify(firstFrame.length > 0)
        fakeFeedback.state = "saving"
        video.color = "tomato"
        waitForRendering(video)
        const secondFrame = capture.capture(video)
        verify(secondFrame.length > 0)
        verify(secondFrame !== firstFrame)
        verify(video.visible)
        compare(video.parent, originalParent)
        compare(video.width, originalWidth)
        compare(preview.thumbnailSource.toString(), firstFrame)
        fakeFeedback.state = "idle"
        compare(preview.thumbnailSource.toString(), "")
    }
    function test_noVideoDoesNotCapture() {
        let calls = 0
        const originalCapture = preview.frameCapture
        preview.frameCapture = { capture: function(surface) { ++calls; return "unexpected" } }
        preview.streaming = false
        preview.prepareThumbnail()
        fakeFeedback.state = "saving"
        compare(calls, 0)
        compare(preview.thumbnailSource.toString(), "")
        verify(preview.visible)
        fakeFeedback.state = "saved"
        compare(preview.captureState, "saved")
        preview.frameCapture = originalCapture
    }
}
