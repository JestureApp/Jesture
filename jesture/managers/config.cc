#include "jesture/managers/config.h"

#include <QMediaDevices>

namespace jesture {

Config::Config(QObject *parent)
    : QObject(parent), camera_device(QMediaDevices::defaultVideoInput()) {}

QCameraDevice Config::cameraDevice() { return camera_device; }

void Config::setCameraDevice(QCameraDevice camera_device) {
    this->camera_device = camera_device;

    emit cameraDeviceChanged(camera_device);
}

void Config::load() {}

void Config::save() {}

}  // namespace jesture