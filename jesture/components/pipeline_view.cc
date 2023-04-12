#include "jesture/components/pipeline_view.h"

#include <QBrush>
#include <QHBoxLayout>
#include <QLabel>
#include <QPen>
#include <QPushButton>
#include <QSizePolicy>

namespace jesture {
PipelineView::PipelineView(Camera* camera, QWidget* parent)
    : QGraphicsView(parent), camera(camera) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    camera_feed = new QGraphicsVideoItem();

    QColor landmark_color1(69, 213, 249, 255 * 0.75);
    // QColor landmark_color1(206, 68, 252, 255 * 0.75);

    QPen landmark_pen1;
    landmark_pen1.setWidth(10);
    landmark_pen1.setBrush(landmark_color1);

    QBrush landmark_brush1(landmark_color1);

    first_hand_landmarks = new LandmarksItem(camera_feed);
    first_hand_landmarks->setPen(landmark_pen1);
    first_hand_landmarks->setBrush(landmark_brush1);

    QColor landmark_color2(Qt::white);
    landmark_color2.setAlpha(256 * 0.75);

    QPen landmark_pen2;
    landmark_pen2.setWidth(10);
    landmark_pen2.setBrush(landmark_color2);

    QBrush landmark_brush2(landmark_color2);

    second_hand_landmarks = new LandmarksItem(camera_feed);
    second_hand_landmarks->setPen(landmark_pen2);
    second_hand_landmarks->setBrush(landmark_brush2);

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

    auto layout = new QHBoxLayout(this);
    auto hint_text = new QLabel("Recording in 3...", this);
    auto stop_recording_button = new QPushButton("Stop Recording", this);
    layout->addWidget(hint_text);
    layout->addWidget(stop_recording_button);
}

QSize PipelineView::sizeHint() const { return sceneRect().size().toSize(); }

void PipelineView::drawLandmarks(std::vector<Landmarks> landmarks) {
    if (landmarks.size() > 0)
        first_hand_landmarks->updateLandmarks(landmarks[0]);

    if (landmarks.size() > 1)
        second_hand_landmarks->updateLandmarks(landmarks[1]);
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
    // Will maintain aspect ratio, cropping when necessary
    fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);

    QGraphicsView::resizeEvent(event);
}

}  // namespace jesture