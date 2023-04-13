#include "jesture/components/gesture_visualization.h"

#include <QLabel>

namespace jesture {
GestureVisualization::GestureVisualization(QWidget* parent)
    : QGraphicsView(parent) {
    auto _ = new QLabel("This a placeholder for a visualization of a gesture!",
                        this);
}

void GestureVisualization::set_gesture(jesturepipe::Gesture gesture) {
    this->gesture = gesture;
}
}  // namespace jesture