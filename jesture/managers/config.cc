#include "jesture/managers/config.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMediaDevices>
#include <QStandardPaths>
#include <filesystem>

#include "absl/types/variant.h"
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

void Config::setAction(int gesture_id, ActionsList action) {
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
        LOG(INFO) << "Loading gestures and actions from " << gestures_file_path;

        QFile gestures_file(gestures_file_path);

        if (!gestures_file.open(QIODevice::ReadOnly)) {
            qFatal("Failed to open %s", config_file_path.c_str());
        }

        QJsonDocument gestures_document =
            QJsonDocument::fromJson(gestures_file.readAll());
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

    QJsonObject gestures_obj;

    for (const auto& [id, gesture] : gestures) {
        QJsonObject gesture_obj;

        QJsonArray frames_arr;

        for (const auto& frame : *gesture.pipe_gesture.frames) {
            QJsonObject frame_obj;

            frame_obj["index_direction"] = frame.hand_shape.index_direction;
            frame_obj["middle_direction"] = frame.hand_shape.middle_direction;
            frame_obj["ring_direction"] = frame.hand_shape.ring_direction;
            frame_obj["pinky_direction"] = frame.hand_shape.pinky_direction;
            frame_obj["thumb_direction"] = frame.hand_shape.thumb_direction;

            if (frame.movement_direction.has_value()) {
                frame_obj["movement_direction"] =
                    frame.movement_direction.value();
            }

            frames_arr.append(frame_obj);
        }

        gesture_obj["frames"] = frames_arr;

        if (actions.find(id) != actions.end()) {
            auto action_list = actions.at(id);
            QJsonObject action_list_obj;

            switch (action_list.cursor_control) {
                case (jesturepipe::CursorControl::Grab):
                    action_list_obj["cursor_control"] = "grab";
                    break;
                case (jesturepipe::CursorControl::Release):
                    action_list_obj["cursor_control"] = "release";
                    break;
                case (jesturepipe::CursorControl::Toggle):
                    action_list_obj["cursor_control"] = "toggle";
                    break;
                default:
                    break;
            }

            QJsonArray actions_arr;
            for (auto action : action_list.action_list) {
                QJsonObject action_obj;

                if (absl::holds_alternative<actions::action::NoOp>(
                        action.pipeline_action)) {
                    action_obj["type"] = "NoOp";
                } else if (absl::holds_alternative<actions::action::KeysPress>(
                               action.pipeline_action)) {
                    action_obj["type"] = "KeysPress";
                    action_obj["sequence"] = action.sequence.toString();
                } else if (absl::holds_alternative<
                               actions::action::KeysRelease>(
                               action.pipeline_action)) {
                    action_obj["type"] = "KeysRelease";
                    action_obj["sequence"] = action.sequence.toString();
                } else if (absl::holds_alternative<actions::action::Keystroke>(
                               action.pipeline_action)) {
                    action_obj["type"] = "Keystroke";
                    action_obj["sequence"] = action.sequence.toString();
                } else if (absl::holds_alternative<actions::action::MousePress>(
                               action.pipeline_action)) {
                    action_obj["type"] = "MousePress";

                    switch (absl::get<actions::action::MousePress>(
                        action.pipeline_action)) {
                        case (actions::action::MousePress::LeftPress):
                            action_obj["button"] = "left";
                            break;
                        case (actions::action::MousePress::MiddlePress):
                            action_obj["button"] = "middle";
                            break;
                        case (actions::action::MousePress::RightPress):
                            action_obj["button"] = "right";
                            break;
                    }
                } else if (absl::holds_alternative<
                               actions::action::MouseRelease>(
                               action.pipeline_action)) {
                    action_obj["type"] = "MouseRelease";

                    switch (absl::get<actions::action::MouseRelease>(
                        action.pipeline_action)) {
                        case (actions::action::MouseRelease::LeftRelease):
                            action_obj["button"] = "left";
                            break;
                        case (actions::action::MouseRelease::MiddleRelease):
                            action_obj["button"] = "middle";
                            break;
                        case (actions::action::MouseRelease::RightRelease):
                            action_obj["button"] = "right";
                            break;
                    }
                } else if (absl::holds_alternative<actions::action::MouseClick>(
                               action.pipeline_action)) {
                    action_obj["type"] = "MouseClick";

                    switch (absl::get<actions::action::MouseClick>(
                        action.pipeline_action)) {
                        case (actions::action::MouseClick::LeftClick):
                            action_obj["button"] = "left";
                            break;
                        case (actions::action::MouseClick::MiddleClick):
                            action_obj["button"] = "middle";
                            break;
                        case (actions::action::MouseClick::RightClick):
                            action_obj["button"] = "right";
                            break;
                    }
                }

                actions_arr.push_back(action_obj);
            }

            action_list_obj["actions"] = actions_arr;

            gesture_obj["action_mapping"] = action_list_obj;
        }

        gestures_obj[gesture.name.c_str()] = gesture_obj;
    }

    QJsonDocument gestures_document(gestures_obj);

    QFile gestures_file(gestures_file_path);

    if (gestures_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&gestures_file);

        out << gestures_document.toJson();

        LOG(INFO) << "Wrote settings to file " << gestures_file_path;
    } else {
        LOG(ERROR) << "Failed to open " << gestures_file_path;
    }

    gestures_file.close();
}

void Config::setToDefaultSettings() {
    setCameraDevice(QMediaDevices::defaultVideoInput());

    setPipelineSettings(false);
}

void Config::setToDefaultGestures() {
    clearGestures();

    int next = addGesture(Gesture("Next", jesturepipe::Gesture::Next()));

    int prev = addGesture(Gesture("Prev", jesturepipe::Gesture::Prev()));

    int slide_left =
        addGesture(Gesture("Slide Left", jesturepipe::Gesture::SlideLeft()));

    int slide_right =
        addGesture(Gesture("Slide Right", jesturepipe::Gesture::SlideRight()));

    setAction(slide_left,
              ActionsList{.action_list = {Keystroke(Qt::Key_PageUp)}});

    setAction(slide_right,
              ActionsList{.action_list = {Keystroke(Qt::Key_PageDown)}});
}

}  // namespace jesture