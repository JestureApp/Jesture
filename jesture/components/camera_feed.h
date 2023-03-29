#ifndef JESTURE_COMPONENTS_FRAME_VIEW_H
#define JESTURE_COMPONENTS_FRAME_VIEW_H

#include <QImage>
#include <QPaintEvent>
#include <QWidget>

#include "mediapipe/framework/port/opencv_core_inc.h"

namespace jesture {
class CameraFeed : public QWidget {
    Q_OBJECT

   public:
    explicit CameraFeed(QWidget *parent = nullptr) noexcept;
    void blur();
    void unblur();

    // protected:
    // void paintEvent(QPaintEvent *event) override;

   private:
    bool painted;
    bool blur_mode;
};
}  // namespace jesture

#endif  // JESTURE_COMPONENTS_FRAME_VIEW_H