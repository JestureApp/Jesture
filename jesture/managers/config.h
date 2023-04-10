#ifndef JESTURE_MANAGERS_CONFIG_H
#define JESTURE_MANAGERS_CONFIG_H

#include <QCameraDevice>
#include <QObject>
#include <map>

#include "jesture/jesturepipe/gesture.h"

namespace jesture {

class Config : public QObject {
    Q_OBJECT

   public:
    explicit Config(QObject *parent = nullptr);

    QCameraDevice cameraDevice() const;
    void setCameraDevice(QCameraDevice camera_device);

    int addGesture(Gesture gesture);
    void removeGesture(int gesture_id);
    void clearGestures();

   public slots:
    void init(bool from_file);
    void save() const;

    void setToDefaultSettings();
    void setToDefaultGestures();

   signals:
    void cameraDeviceChanged(QCameraDevice camera_device);

    void gestureChanged(int gesture_id, Gesture gesture);
    void gestureRemoved(int gesture_id);
    void gesturesCleared();

   private:
    int next_gesture_id;

    QCameraDevice camera_device;
    std::map<int, Gesture> gestures;
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CONFIG_H