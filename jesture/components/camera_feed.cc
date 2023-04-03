#include "jesture/components/camera_feed.h"

#include <QMediaCaptureSession>

namespace jesture {

CameraFeed::CameraFeed(Camera* camera, QGraphicsItem* parent)
    : QGraphicsVideoItem(parent) {
    auto capture_session = new QMediaCaptureSession(this);
    capture_session->setCamera(camera);
    capture_session->setVideoOutput(this);

    updateFromDevice(camera->cameraDevice());

    camera->start();
}

void CameraFeed::updateFromDevice(const QCameraDevice& camera_device) {
    auto position = camera_device.position();

    // if (position != QCameraDevice::BackFace) {
    // setRotation(180);
    // }
}

}  // namespace jesture