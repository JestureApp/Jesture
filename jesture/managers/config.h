#ifndef JESTURE_MANAGERS_CONFIG_H
#define JESTURE_MANAGERS_CONFIG_H

#include <QCameraDevice>
#include <QObject>
#include <map>

#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"

namespace jesture {

class Config : public QObject {
    Q_OBJECT

   public:
    explicit Config(QObject* parent = nullptr);
    QCameraDevice cameraDevice() const;

   public slots:
    int addGesture(Gesture gesture);
    void removeGesture(int gesture_id);
    void clearGestures();

    void setAction(int gesture_id, Action action);
    void removeAction(int gesture_id);

    void init(bool from_file);
    void save() const;

    void setToDefaultSettings();
    void setToDefaultGestures();

    void set_camera_from_description(const QString& camera_description);
    void setCameraDevice(QCameraDevice camera_device);

   signals:
    void cameraDeviceChanged(QCameraDevice camera_device);

    void gestureChanged(int gesture_id, Gesture gesture);
    void gestureRemoved(int gesture_id);
    void gesturesCleared();

    void actionChanged(int gesture_id, Action action);
    void actionRemoved(int gesture_id);

   private:
    int next_gesture_id;

    QCameraDevice camera_device;
    std::map<int, Gesture> gestures;
    std::map<int, Action> actions;
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CONFIG_H