#include "jesture/managers/camera.h"

namespace jesture {

Camera::Camera(QObject *parent) : QCamera(parent) {
    QObject::connect(this, &QCamera::cameraDeviceChanged, this,
                     [this]() { emit deviceChanged(cameraDevice()); });
}

bool Camera::shouldReflect() const {
    return cameraDevice().position() != QCameraDevice::BackFace;
}

void Camera::setDevice(const QCameraDevice &device) { setCameraDevice(device); }

}  // namespace jesture