#include "jesture/components/gesture_list_view.h"

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "jesture/components/gesture_list_item.h"
#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesture {
GestureListView::GestureListView(Resources* resources, QWidget* parent)
    : QWidget(parent) {
    layout = new QVBoxLayout(this);

    auto title = new QLabel("Gesture List", this);
    auto add_gesture_button = new QPushButton("Record A New Gesture", this);

    connect(add_gesture_button, &QPushButton::released, this,
            &GestureListView::record_gesture);

    layout->addWidget(title);
    layout->addWidget(add_gesture_button);

    cross_icon = resources->cross_icon();
}

void GestureListView::add_gesture(int id, Gesture gesture) {
    auto gesture_list_item =
        new GestureListItem(id, gesture, NULL, cross_icon, this);
    layout->addWidget(gesture_list_item);
}
}  // namespace jesture
