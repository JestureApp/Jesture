#ifndef JESTURE_COMPONENTS_FRAME_VIEW_H
#define JESTURE_COMPONENTS_FRAME_VIEW_H

#include <QImage>
#include <QPaintEvent>
#include <QWidget>

#include "mediapipe/framework/port/opencv_core_inc.h"

namespace jesture {
class FrameView : public QWidget {
    Q_OBJECT

   public:
    explicit FrameView(QWidget *parent = nullptr) noexcept;
    void blur();
    void unblur();

   public slots:
    void setFrame(cv::Mat);

   protected:
    void paintEvent(QPaintEvent *event) override;

   private:
    QImage img;
    bool painted;
    bool blur_mode;
};
}  // namespace jesture

#endif  // JESTURE_COMPONENTS_FRAME_VIEW_H