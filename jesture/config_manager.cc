#include "config_manager.h"

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QJsonDocument>
#include <QtCore/QStandardPaths>
#include <QtCore/QTextStream>

const char* default_gestures = R"(
[
    {
        "name": "Peace"
    },
    {
        "name": "Point"
    },
    {
        "name": "Thumbs Up"
    },
    {
        "name": "Swipe"
    }
]
)";

const char* default_settings = R"(
{
    "accuracy": 0,
    "camera": 0,
    "hands": 2
}
)";

ConfigManager::ConfigManager() {
    gestures = nullptr;
    settings = nullptr;

    load_gestures();
    load_settings();
}

void ConfigManager::save() {
    write_gestures();
    write_settings();
}

void ConfigManager::write_gestures() {
    QDir().mkpath(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QFile* gestures_file = new QFile(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/gestures.json");
    gestures_file->open(QIODevice::WriteOnly);
    QTextStream out(gestures_file);
    out << gestures->toJson();
}

void ConfigManager::write_settings() {
    QDir().mkpath(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QFile* settings_file = new QFile(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/settings.json");
    settings_file->open(QIODevice::WriteOnly);
    QTextStream out(settings_file);
    out << settings->toJson();
}

void ConfigManager::load_gestures() {
    QString app_data_path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile* gestures_file = new QFile(app_data_path + "/gestures.json");
    if (gestures_file->exists()) {
        gestures_file->open(QIODevice::ReadOnly);
        gestures = new QJsonDocument(
            QJsonDocument::fromJson(gestures_file->readAll()));
    }

    if (!gestures || gestures->toJson() == "") {
        gestures = new QJsonDocument(QJsonDocument::fromJson(default_gestures));
    }
}

void ConfigManager::load_settings() {
    QString app_data_path =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile* settings_file = new QFile(app_data_path + "/settings.json");
    if (settings_file->exists()) {
        settings_file->open(QIODevice::ReadOnly);
        settings = new QJsonDocument(
            QJsonDocument::fromJson(settings_file->readAll()));
    }

    if (!settings || settings->toJson() == "") {
        settings = new QJsonDocument(QJsonDocument::fromJson(default_settings));
    }
}