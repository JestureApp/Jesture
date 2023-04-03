#include "jesture/managers/camera.h"

namespace jesture {

Camera::Camera(QObject *parent) : QCamera(parent), capture_session(nullptr) {
    QObject::connect(this, &QCamera::cameraDeviceChanged, this,
                     [this]() { emit deviceChanged(cameraDevice()); });
}

bool Camera::shouldReflect() const {
    return cameraDevice().position() != QCameraDevice::BackFace;
}

void Camera::setDevice(const QCameraDevice &device) { setCameraDevice(device); }

VideoCaptureSession *Camera::captureSession() {
    if (!capture_session) {
        capture_session = new VideoCaptureSession(this, this);
    }

    return capture_session;
}

}  // namespace jesture