#include "jesture/components/frame_view.h"

#include <QPainter>
#include <QGraphicsBlurEffect>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QSize>
#include <QRectF>

#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {



FrameView::FrameView(QWidget *parent) noexcept
    : QWidget(parent), painted(true), blur_mode(false) {}

void FrameView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage* drawn_image = &img;
    
    if (!drawn_image->isNull()) {
        if (blur_mode) {
            // From https://stackoverflow.com/questions/14915129/qimage-transform-using-qgraphicsblureffect
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
            scene.render(blur_painter, QRectF(), QRectF(0, 0, img.width(), img.height()));
        }
        
        setAttribute(Qt::WA_OpaquePaintEvent);
        painter.drawImage(0, 0, drawn_image->scaled(size()));
        painted = true;
    }
}

void FrameView::setFrame(cv::Mat frame) {
    Q_ASSERT(frame.type() == CV_8UC3);

    int w = frame.cols / 3, h = frame.rows / 3;

    if (img.size() != QSize{w, h}) img = QImage(w, h, QImage::Format_RGB888);

    cv::Mat mat(h, w, CV_8UC3, img.bits(), img.bytesPerLine());
    cv::resize(frame, mat, mat.size(), 0, 0, cv::INTER_AREA);

    update();
}

void FrameView::blur() {
    blur_mode = true;
}

void FrameView::unblur() {
    blur_mode = false;
}

}  // namespace jesture