#ifndef JESTURE_MANAGERS_CONFIG_H
#define JESTURE_MANAGERS_CONFIG_H

#include <QCameraDevice>
#include <QObject>

namespace jesture {

class Config : public QObject {
    Q_OBJECT

   public:
    explicit Config(QObject *parent = nullptr);

    QCameraDevice cameraDevice();
    void setCameraDevice(QCameraDevice camera_device);

   public slots:
    void load();
    void save();

   signals:
    void cameraDeviceChanged(QCameraDevice camera_device);

   private:
    QCameraDevice camera_device;
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CONFIG_H