#include "jesture/managers/camera.h"

namespace jesture {

Camera::Camera(QObject *parent) : QCamera(parent) {}

void Camera::setDevice(const QCameraDevice &device) { setCameraDevice(device); }

}  // namespace jesture