#ifndef JESTURE_COMPONENTS_CAMERA_FEED_H
#define JESTURE_COMPONENTS_CAMERA_FEED_H

#include <QGraphicsVideoItem>
#include <QObject>

#include "jesture/managers/camera.h"

namespace jesture {

class CameraFeed : public QGraphicsVideoItem {
    Q_OBJECT

   public:
    CameraFeed(Camera* camera, QGraphicsItem* parent = nullptr);

   public slots:
    void updateFromDevice(const QCameraDevice& camera_device);
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_CAMERA_FEED_H