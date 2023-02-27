#ifndef JESTURE_CONFIG_MANAGER_H
#define JESTURE_CONFIG_MANAGER_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>

class ConfigManager : public QObject {
Q_OBJECT

public:
    ConfigManager();
public slots:
    void save();
    /*void write_accuracy_setting(int level);
    void write_camera_setting(int index);
    void write_hands_setting(int hands);*/
private:
    void write_gestures();
    void write_settings();
    void load_gestures();
    void load_settings();
    
    QJsonDocument* gestures;
    QJsonDocument* settings;
};
#endif