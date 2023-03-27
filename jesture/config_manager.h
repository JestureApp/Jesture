#ifndef JESTURE_CONFIG_MANAGER_H
#define JESTURE_CONFIG_MANAGER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QtCore/QObject>
#include <vector>

#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"

class ConfigManager : public QObject {
    Q_OBJECT

   public:
    ConfigManager();
    jesture::JesturePipeSettings get_settings();
    std::vector<jesturepipe::Gesture> get_gestures();
   signals:
    void settings_to_controller(jesture::JesturePipeSettings settings);
    void new_gesture(int gesture_id, jesturepipe::Gesture gesture);
   public slots:
    void save();
    void update_camera_setting(int index);
    void consider_gesture(jesturepipe::Gesture gesture);

   private:
    void write_gestures();
    void write_settings();
    void load_gestures();
    void load_settings();
    const char* default_settings_string();
    const char* default_gestures_string();
    jesturepipe::Gesture gesture_from_json(QJsonObject gesture);
    QJsonObject gesture_to_json(jesturepipe::Gesture);

    QJsonArray gestures;
    QJsonObject settings;
};
#endif