#include "jesture/components/pipeline_view.h"

#include <QMediaCaptureSession>

namespace jesture {
PipelineView::PipelineView(Camera* camera, QWidget* parent)
    : QGraphicsView(parent), camera(camera) {
    camera_feed = new QGraphicsVideoItem();

    auto capture_session = new QMediaCaptureSession(this);
    capture_session->setCamera(camera);
    capture_session->setVideoOutput(camera_feed);

    scene = new QGraphicsScene(this);
    scene->addItem(camera_feed);

    setScene(scene);
    updateSizes(camera_feed->nativeSize());
    QObject::connect(camera_feed, &QGraphicsVideoItem::nativeSizeChanged, this,
                     &PipelineView::updateSizes);

    updateReflection();
    QObject::connect(camera, &Camera::cameraDeviceChanged, this,
                     &PipelineView::updateReflection);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Ensure camera is running
    camera->start();
}

void PipelineView::updateSizes(const QSizeF& size) {
    scene->setSceneRect(0, 0, size.width(), size.height());

    camera_feed->setSize(scene->sceneRect().size());

    updateReflection();

    fitInView(scene->sceneRect());
}

void PipelineView::updateReflection() {
    if (camera->shouldReflect()) {
        QTransform transform;
        transform.scale(-1, 1);
        transform.translate(-scene->sceneRect().width(), 0);
        camera_feed->setTransform(transform);
    } else {
        camera_feed->resetTransform();
    }
}

void PipelineView::resizeEvent(QResizeEvent* event) {
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    QGraphicsView::resizeEvent(event);
}

}  // namespace jesture