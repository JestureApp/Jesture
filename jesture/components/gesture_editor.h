#ifndef JESTURE_COMPONENTS_GESTURE_EDITOR_H
#define JESTURE_COMPONENTS_GESTURE_EDITOR_H

#include <QObject>
#include <QWidget>

#include "jesture/components/frame_view.h"
#include "jesture/jesturepipe/controller.h"

namespace jesture {

class GestureEditor : public QWidget {
    Q_OBJECT

   public:
    explicit GestureEditor(JesturePipeController* controller,
                           QWidget* parent = nullptr) noexcept;

   private:
    JesturePipeController* controller;
    FrameView* frame_view;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_EDITOR_H