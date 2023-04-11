#include "jesture/components/gesture_list_view.h"

#include <QLabel>

namespace jesture {
GestureListView::GestureListView(QWidget* parent) : QWidget(parent) {
    auto title = new QLabel("Gesture List", this);
}
}  // namespace jesture
