#include "jesture/components/gesture_list_view.h"

#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "jesture/components/gesture_list_item.h"
#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/managers/config.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesture {
GestureListView::GestureListView(Resources* resources, Config* config,
                                 QWidget* parent)
    : QWidget(parent), config(config) {
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

    connect(gesture_list_item, &GestureListItem::delete_gesture, config,
            &Config::removeGesture);
    connect(gesture_list_item, &GestureListItem::delete_gesture, this,
            &GestureListView::delete_list_item);
}

void GestureListView::delete_list_item() {
    GestureListItem* list_item = qobject_cast<GestureListItem*>(sender());
    layout->removeWidget(list_item);
    delete list_item;
}
}  // namespace jesture
