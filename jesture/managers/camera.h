#ifndef JESTURE_MANAGERS_CAMERA_H
#define JESTURE_MANAGERS_CAMERA_H

#include <QCamera>
#include <QObject>

namespace jesture {

class Camera : public QCamera {
    Q_OBJECT

   public:
    explicit Camera(QObject* parent = nullptr);

    bool shouldReflect() const;

   public slots:
    void setDevice(const QCameraDevice& device);

   signals:
    void deviceChanged(const QCameraDevice& device);
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CAMERA_H