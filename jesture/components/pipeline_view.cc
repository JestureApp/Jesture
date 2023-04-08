#include "jesture/components/pipeline_view.h"

#include <QBrush>
#include <QPen>

namespace jesture {
PipelineView::PipelineView(Camera* camera, QWidget* parent)
    : QGraphicsView(parent), camera(camera) {
    camera_feed = new QGraphicsVideoItem();

    QColor landmark_color(Qt::white);
    landmark_color.setAlpha(256 * 0.75);

    QPen landmark_pen;
    landmark_pen.setWidth(10);
    landmark_pen.setBrush(landmark_color);

    QBrush landmark_brush(landmark_color);

    first_hand_landmarks = new LandmarksItem(camera_feed);
    first_hand_landmarks->setPen(landmark_pen);
    first_hand_landmarks->setBrush(landmark_brush);

    second_hand_landmarks = new LandmarksItem(camera_feed);
    second_hand_landmarks->setPen(landmark_pen);
    second_hand_landmarks->setBrush(landmark_brush);

    auto capture_session = camera->captureSession();
    capture_session->addVideoSink(camera_feed->videoSink());

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

void PipelineView::drawLandmarks(std::vector<Landmarks> landmarks) {
    if (landmarks.size() > 0)
        first_hand_landmarks->updateLandmarks(landmarks[0]);

    if (landmarks.size() > 1) second_hand_landmarks->setVisible(true);
}

void PipelineView::updateSizes(const QSizeF& size) {
    scene->setSceneRect(0, 0, size.width(), size.height());

    camera_feed->setSize(scene->sceneRect().size());

    first_hand_landmarks->setSize(scene->sceneRect().size());
    second_hand_landmarks->setSize(scene->sceneRect().size());

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