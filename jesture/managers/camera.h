#ifndef JESTURE_MANAGERS_CAMERA_H
#define JESTURE_MANAGERS_CAMERA_H

#include <QCamera>
#include <QObject>

#include "jesture/util/video_capture_session.h"

namespace jesture {

class Camera : public QCamera {
    Q_OBJECT

   public:
    explicit Camera(QObject* parent = nullptr);

    bool shouldReflect() const;

    VideoCaptureSession* captureSession();

   public slots:
    void setDevice(const QCameraDevice& device);

   signals:
    void deviceChanged(const QCameraDevice& device);

   private:
    VideoCaptureSession* capture_session;
};

}  // namespace jesture

#endif  // JESTURE_MANAGERS_CAMERA_H