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

    const std::map<int, Gesture>& getGestures() const;
    const std::map<int, ActionsList>& getActions() const;

   public slots:
    void setCameraDevice(QCameraDevice camera_device);

    int addGesture(Gesture gesture);
    void removeGesture(int gesture_id);
    void clearGestures();

    void setAction(int gesture_id, ActionsList action);
    void removeAction(int gesture_id);

    void setPipelineSettings(bool use_full);

    void init(bool from_file);
    void save() const;

    void setToDefaultSettings();
    void setToDefaultGestures();

   signals:
    void cameraDeviceChanged(QCameraDevice camera_device);

    void gestureChanged(int gesture_id, Gesture gesture);
    void gestureRemoved(int gesture_id);
    void gesturesCleared();

    void actionChanged(int gesture_id, ActionsList action);
    void actionRemoved(int gesture_id);

    void pipelineSettingsChanged(bool use_full);

   private:
    int next_gesture_id;

    bool use_full;

    QCameraDevice camera_device;
    std::map<int, Gesture> gestures;
    std::map<int, ActionsList> actions;
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CONFIG_H