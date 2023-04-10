#include "jesture/managers/config.h"

#include <QMediaDevices>

namespace jesture {

Config::Config(QObject *parent) : QObject(parent), next_gesture_id(0) {}

QCameraDevice Config::cameraDevice() const { return camera_device; }

void Config::setCameraDevice(QCameraDevice camera_device) {
    this->camera_device = camera_device;

    emit cameraDeviceChanged(camera_device);
}

int Config::addGesture(Gesture gesture) {
    gestures[next_gesture_id] = gesture;

    emit gestureChanged(next_gesture_id, gesture);

    return next_gesture_id++;
}

void Config::removeGesture(int gesture_id) {
    gestures.erase(gesture_id);

    emit gestureRemoved(gesture_id);
}

void Config::clearGestures() {
    gestures.clear();

    next_gesture_id = 0;

    emit gesturesCleared();
}

void Config::init(bool from_file) {
    if (!from_file) {
        setToDefaultSettings();
        setToDefaultGestures();

        return;
    }

    // TODO
}

void Config::save() const {
    // TODO
}

void Config::setToDefaultSettings() {
    camera_device = QMediaDevices::defaultVideoInput();
}

void Config::setToDefaultGestures() {
    clearGestures();

    addGesture(Gesture("Stop", jesturepipe::Gesture::Stop()));

    addGesture(Gesture("Next", jesturepipe::Gesture::Next()));

    addGesture(Gesture("Prev", jesturepipe::Gesture::Prev()));

    addGesture(Gesture("Slide Left", jesturepipe::Gesture::SlideLeft()));

    addGesture(Gesture("Slide Right", jesturepipe::Gesture::SlideRight()));
}

}  // namespace jesture