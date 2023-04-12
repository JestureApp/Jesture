#include "jesture/managers/config.h"

#include <QMediaDevices>

namespace jesture {

Config::Config(QObject* parent) : QObject(parent), next_gesture_id(0) {}

QCameraDevice Config::cameraDevice() const { return camera_device; }

void Config::set_camera_from_description(const QString& camera_description) {
    for (const auto& camera : QMediaDevices::videoInputs()) {
        if (camera.description() == camera_description) {
            setCameraDevice(camera);
            return;
        }
    }
}

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
    actions.clear();

    next_gesture_id = 0;

    emit gesturesCleared();
}

void Config::setAction(int gesture_id, Action action) {
    actions[gesture_id] = action;

    emit actionChanged(gesture_id, action);
}

void Config::removeAction(int gesture_id) {
    actions.erase(gesture_id);

    emit actionRemoved(gesture_id);
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

    int stop = addGesture(Gesture("Stop", jesturepipe::Gesture::Stop()));

    int next = addGesture(Gesture("Next", jesturepipe::Gesture::Next()));

    int prev = addGesture(Gesture("Prev", jesturepipe::Gesture::Prev()));

    int slide_left =
        addGesture(Gesture("Slide Left", jesturepipe::Gesture::SlideLeft()));

    int slide_right =
        addGesture(Gesture("Slide Right", jesturepipe::Gesture::SlideRight()));

    setAction(stop, {.type = actions::action::NoOp(),
                     .cursor_control = jesturepipe::CursorControl::Toggle});
}

}  // namespace jesture