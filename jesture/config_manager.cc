#include "config_manager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextStream>
#include <vector>

#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"

ConfigManager::ConfigManager() {
    load_gestures();
    load_settings();
}

jesture::JesturePipeSettings ConfigManager::get_settings() {
    return {
        .camera_index = settings["camera"].toInt(
            0),  // Parameter passed to .toInt will be the fallback value
        .use_full = settings["use_full"].toBool(false),
    };
}

std::vector<jesturepipe::Gesture> ConfigManager::get_gestures() {
    std::vector<jesturepipe::Gesture> gesture_list;
    for (const auto gesture : gestures) {
        gesture_list.push_back(gesture_from_json(gesture.toObject()));
    }
    return gesture_list;
}

void ConfigManager::save() {
    write_gestures();
    write_settings();
}

void ConfigManager::update_camera_setting(int index) {
    settings["camera"] = index;
    settings_to_controller(get_settings());
}

void ConfigManager::consider_gesture(jesturepipe::Gesture new_gesture) {
    gestures.push_back(gesture_to_json(new_gesture));
}

void ConfigManager::write_gestures() {
    // Create path and new writable file if it doesn't exist already
    QDir().mkpath(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QFile* gestures_file = new QFile(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/gestures.json");

    // Use JSON document class to format JSON string
    QJsonDocument document(gestures);

    // Write to file
    gestures_file->open(QIODevice::WriteOnly);
    QTextStream out(gestures_file);
    out << document.toJson();
}

void ConfigManager::write_settings() {
    // Create path and new writable file
    QDir().mkpath(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QFile* settings_file = new QFile(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/settings.json");

    // Use JSON document class to format JSON string
    QJsonDocument document(settings);

    // Write to file
    settings_file->open(QIODevice::WriteOnly);
    QTextStream out(settings_file);
    out << document.toJson();
}

void ConfigManager::load_gestures() {
    // Use JSON document class to parse JSON
    bool gestures_found = false;
    QJsonDocument document;

    // Construct gestures file path
    QString app_data_path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile* gestures_file = new QFile(app_data_path + "/gestures.json");

    // If gestures file exists, load it
    if (gestures_file->exists()) {
        gestures_file->open(QIODevice::ReadOnly);
        document = QJsonDocument::fromJson(gestures_file->readAll());
    }

    // Otherwise, use default settings
    if (!gestures_found || document.toJson() == "") {
        document = QJsonDocument::fromJson(default_gestures_string());
    }

    // From JSON document, get the parent array
    gestures = document.array();
}

void ConfigManager::load_settings() {
    // Use JSON document class to parse JSON
    bool settings_found = false;
    QJsonDocument document;

    // Construct settings file path
    QString app_data_path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile* settings_file = new QFile(app_data_path + "/settings.json");

    // If settings file exists, load it
    if (settings_file->exists()) {
        settings_file->open(QIODevice::ReadOnly);
        document = QJsonDocument::fromJson(settings_file->readAll());
        settings_found = true;
    }

    // Otherwise, use default settings
    if (!settings_found || document.toJson() == "") {
        document = QJsonDocument::fromJson(default_settings_string());
    }

    // From JSON document, get the parent object
    settings = document.object();
}

const char* ConfigManager::default_gestures_string() {
    return R"(
    [
        {
            "name": "Stop",
            "frames": [
                [90, 90, 90, 90, 90]
            ]
        }
    ]
    )";
}

const char* ConfigManager::default_settings_string() {
    return R"(
    {
        "accuracy": 0,
        "camera": 0,
        "hands": 2,
        "mode": 1
    }
    )";
}

jesturepipe::Gesture ConfigManager::gesture_from_json(
    QJsonObject gesture_json) {
    std::vector<jesturepipe::GestureFrame> frames;

    for (auto frame : gesture_json["frames"].toArray()) {
        frames.push_back(jesturepipe::GestureFrame{
            {frame[0].toDouble(), frame[1].toDouble(), frame[2].toDouble(),
             frame[3].toDouble(), frame[4].toDouble()}});
    }
    return jesturepipe::Gesture(std::move(frames));
}

QJsonObject ConfigManager::gesture_to_json(jesturepipe::Gesture gesture) {
    /*QJsonObject gesture_json;
    QJsonArray gesture_frames;
    gesture_json["name"] = "New Gesture";
    int index = 0;
    for (auto frame : gesture.frames) {
        QJsonArray new_frame;
        new_frame[0] = frame.1;
        new_frame[1] = frame.2;
        new_frame[2] = frame.3;
        new_frame[3] = frame.4;
        new_frame[4] = frame.5;

        gesture_frames[index] = new_frame;

        index++;
    }
    gesture_json["frames"] = gesture_frames;
    return gesture_json;*/
}