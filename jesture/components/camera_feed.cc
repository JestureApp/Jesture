#include "jesture/components/camera_feed.h"

#include <QCamera>
#include <QGraphicsBlurEffect>
#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QImage>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QPainter>
#include <QPixmap>
#include <QRectF>
#include <QSize>

#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {

CameraFeed::CameraFeed(QWidget* parent) noexcept
    : QWidget(parent), painted(true), blur_mode(false) {
    // Get first camera device
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    auto camera = new QCamera(cameras[0]);
    camera->start();

    // Create a graphics item to display video
    auto camera_graphics = new QGraphicsVideoItem;
    camera_graphics->setPos(0, -120);
    camera_graphics->setScale(4);

    // Create a capture session for piping data from camera to video
    auto capture_session = new QMediaCaptureSession;
    capture_session->setCamera(camera);
    capture_session->setVideoOutput(camera_graphics);

    // Create a scene for the video item
    auto scene = new QGraphicsScene;
    scene->addItem(camera_graphics);

    // Create a view for the scene
    auto view = new QGraphicsView(scene, parent);
    view->setSceneRect(0, 0, 1280, 720);
    view->resize(1280, 720);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Display this widget
    view->show();
}
/*
OLD BACKGROUND BLURRING CODE

void CameraFeed::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage *drawn_image = &img;

    if (!drawn_image->isNull()) {
        if (blur_mode) {
            // From
            //
    https://stackoverflow.com/questions/14915129/qimage-transform-using-qgraphicsblureffect
            auto blur_effect = new QGraphicsBlurEffect(this);
            blur_effect->setBlurRadius(8);
            QGraphicsScene scene;
            QGraphicsPixmapItem item;
            item.setPixmap(QPixmap::fromImage(img));
            item.setGraphicsEffect(blur_effect);
            scene.addItem(&item);
            drawn_image = new QImage(img.size(), QImage::Format_ARGB32);
            drawn_image->fill(Qt::transparent);
            auto blur_painter = new QPainter(drawn_image);
            scene.render(blur_painter, QRectF(),
                         QRectF(0, 0, img.width(), img.height()));
        }

        setAttribute(Qt::WA_OpaquePaintEvent);
        painter.drawImage(0, 0, drawn_image->scaled(size()));
        painted = true;
    }
}
*/

void CameraFeed::blur() { blur_mode = true; }

void CameraFeed::unblur() { blur_mode = false; }

}  // namespace jesture