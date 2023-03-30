import QtQuick 6.3
import QtQuick.Window
import QtMultimedia 

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MediaDevices {
        id: mediaDevices
    }

    CaptureSession{
        camera: Camera {
            id: camera
            cameraDevice: mediaDevices.defaultVideoInput
        }

        videoOutput: viewfinder
    }

    VideoOutput {
        id: viewfinder

        x: 0
        y: 0
        width: parent.width
        height: parent.height
    }
}