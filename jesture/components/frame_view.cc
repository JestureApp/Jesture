#include "jesture/components/frame_view.h"

#include <QPainter>

#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {

FrameView::FrameView(QWidget *parent) noexcept
    : QWidget(parent), painted(true) {}

void FrameView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!img.isNull()) {
        setAttribute(Qt::WA_OpaquePaintEvent);
        painter.drawImage(0, 0, img.scaled(size()));
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

}  // namespace jesture