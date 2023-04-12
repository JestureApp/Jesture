#include "jesture/managers/config.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMediaDevices>
#include <QStandardPaths>
#include <filesystem>

#include "glog/logging.h"

namespace jesture {

namespace fs = std::filesystem;

Config::Config(QObject* parent)
    : QObject(parent), next_gesture_id(0), use_full(false) {}

QCameraDevice Config::cameraDevice() const { return camera_device; }

void Config::setCameraDevice(QCameraDevice camera_device) {
    this->camera_device = camera_device;

    LOG(INFO) << "Set camera device to "
              << camera_device.description().toStdString();

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

void Config::setPipelineSettings(bool use_full) {
    this->use_full = use_full;

    LOG(INFO) << "Set pipeline settings to use_full=" << use_full;

    emit pipelineSettingsChanged(use_full);
}

void Config::init(bool from_file) {
    if (!from_file) {
        setToDefaultSettings();
        setToDefaultGestures();

        return;
    }

    fs::path config_dir_path = fs::path(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
            .toStdString());

    fs::path config_file_path = config_dir_path / "settings.json";
    fs::path gestures_file_path = config_dir_path / "gestures.json";

    if (!fs::exists(config_file_path)) {
        setToDefaultSettings();
    } else {
        LOG(INFO) << "Loading settings from " << config_file_path;

        QFile settings_file(config_file_path);

        if (!settings_file.open(QIODevice::ReadOnly)) {
            qFatal("Failed to open %s", config_file_path.c_str());
        }

        QJsonDocument settings_document =
            QJsonDocument::fromJson(settings_file.readAll());

        use_full = settings_document["use_full"].toBool();

        int camera_id = settings_document["camera_id"].toInt();
        bool found = false;

        for (auto camera_device : QMediaDevices::videoInputs()) {
            if (camera_device.id().toInt() == camera_id) {
                setCameraDevice(camera_device);
                found = true;
                break;
            }
        }

        if (!found) {
            qFatal("Failed to find camera device with id %d", camera_id);
        }

        settings_file.close();
    }

    if (!fs::exists(gestures_file_path)) {
        setToDefaultGestures();
    } else {
        // TODO
    }
}

void Config::save() const {
    QDir().mkpath(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));

    fs::path config_dir_path = fs::path(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
            .toStdString());

    fs::path config_file_path = config_dir_path / "settings.json";
    fs::path gestures_file_path = config_dir_path / "gestures.json";

    QJsonObject settings;

    settings["use_full"] = use_full;
    settings["camera_id"] = camera_device.id().toInt();

    QJsonDocument settings_document(settings);

    QFile settings_file(config_file_path);

    if (settings_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&settings_file);

        out << settings_document.toJson();

        LOG(INFO) << "Wrote settings to file " << config_file_path;
    } else {
        LOG(ERROR) << "Failed to open " << config_file_path;
    }

    settings_file.close();
}

void Config::setToDefaultSettings() {
    setCameraDevice(QMediaDevices::defaultVideoInput());

    setPipelineSettings(false);
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