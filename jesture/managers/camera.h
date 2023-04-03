#ifndef JESTURE_MANAGERS_CAMERA_H
#define JESTURE_MANAGERS_CAMERA_H

#include <QCamera>
#include <QObject>

namespace jesture {

class Camera : public QCamera {
    Q_OBJECT

   public:
    Camera(QObject* parent = nullptr);

   public slots:
    void setDevice(const QCameraDevice& device);
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CAMERA_H