import QtQuick
import QtQuick.Controls
import QGroundControl.ScreenTools

Rectangle {
    id: root
    property var feedback: null
    property var videoSurface: null
    property bool streaming: false
    property url thumbnailSource: ""
    property var frameCapture: null
    readonly property string captureState: feedback ? feedback.state : "idle"

    width: ScreenTools.defaultFontPixelHeight * 10
    height: width * 9 / 16 + caption.height
    visible: captureState !== "idle"
    color: "#dd161b20"
    border.width: 2
    border.color: captureState === "saved" ? "#39cf7b" : "#ffffff"
    radius: 6
    clip: true
    // Keep the preview's textures, clipping and spinner in their own render pass.
    // Only its finished texture is composited beside the native GStreamer surface.
    layer.enabled: visible
    layer.smooth: true

    // Prepare while the feedback card is hidden, before sending the capture command.
    function prepareThumbnail() {
        thumbnailSource = streaming && frameCapture && videoSurface
            ? frameCapture.capture(videoSurface) : ""
    }

    onCaptureStateChanged: {
        if (captureState === "idle") {
            thumbnailSource = ""
        }
    }

    Item {
        id: imageArea
        width: parent.width
        height: width * 9 / 16
        Image {
            anchors.fill: parent
            source: root.thumbnailSource
            fillMode: Image.PreserveAspectCrop
            cache: false
        }
        Label {
            anchors.centerIn: parent
            visible: root.thumbnailSource.toString().length === 0
            text: qsTr("プレビューなし")
            color: "#aaaaaa"
            font.pixelSize: ScreenTools.defaultFontPixelHeight * 0.75
        }
        Rectangle {
            anchors.fill: parent
            color: "#66000000"
        }
        Rectangle {
            id: savingIndicator
            anchors.centerIn: parent
            width: ScreenTools.defaultFontPixelHeight * 3.2
            height: width
            radius: width / 2
            color: "#f5101820"
            border.color: "#88ffffff"
            border.width: 1
            visible: root.captureState === "saving"

            Item {
                id: loadingRing
                anchors.fill: parent
                anchors.margins: parent.width * 0.14

                Repeater {
                    model: 12
                    Item {
                        required property int index
                        anchors.fill: parent
                        rotation: index * 30
                        opacity: 0.45 + index / 11 * 0.55

                        Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.top
                            width: loadingRing.width * 0.14
                            height: width
                            radius: width / 2
                            color: "#ffffff"
                        }
                    }
                }

                RotationAnimation on rotation {
                    from: 0
                    to: 360
                    duration: 1000
                    loops: Animation.Infinite
                    running: savingIndicator.visible && root.visible
                }
            }
        }
        Label {
            anchors.centerIn: parent
            visible: root.captureState !== "saving"
            text: root.captureState === "saved" ? "✓" : root.captureState === "failed" ? "✕" : "?"
            color: root.captureState === "saved" ? "#39cf7b" : root.captureState === "failed" ? "#ff6868" : "#ffcc66"
            font.pixelSize: ScreenTools.defaultFontPixelHeight * 2.8
            font.bold: true
        }
    }
    Label {
        id: caption
        anchors.top: imageArea.bottom
        width: parent.width
        height: ScreenTools.defaultFontPixelHeight * 2.2
        padding: 4
        text: root.captureState === "saving" ? qsTr("保存中…")
            : root.captureState === "saved" ? qsTr("写真を保存しました")
            : root.captureState === "failed" ? qsTr("写真の保存に失敗しました")
            : qsTr("保存を確認できません")
        color: "white"
        font.pixelSize: ScreenTools.defaultFontPixelHeight * 0.75
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
    }
}
