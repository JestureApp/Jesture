#include "jesture/components/gesture_list_view.h"

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "jesture/components/gesture_list_item.h"
#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/managers/config.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesture {
GestureListView::GestureListView(Resources* resources, Config* config,
                                 QWidget* parent)
    : QWidget(parent), config(config) {
    auto layout = new QVBoxLayout(this);
    auto title = new QLabel("Gesture List", this);
    auto list_view = new QWidget(this);
    list_layout = new QVBoxLayout(list_view);
    auto add_gesture_button = new QPushButton("Record A New Gesture", this);

    title->setStyleSheet(
        "font-size: 24px; font-weight: 700; margin-bottom: 12px;");

    connect(add_gesture_button, &QPushButton::released, this,
            &GestureListView::record_gesture);

    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(title);
    layout->addWidget(list_view);
    layout->addWidget(add_gesture_button);
    list_layout->setAlignment(Qt::AlignTop);

    cross_icon = resources->cross_icon();
}

void GestureListView::add_gesture(int id, Gesture gesture) {
    auto gesture_list_item = new GestureListItem(id, gesture, cross_icon);
    list_layout->addWidget(gesture_list_item);

    connect(gesture_list_item, &GestureListItem::update_action, config,
            &Config::setAction);
    connect(gesture_list_item, &GestureListItem::delete_gesture, config,
            &Config::removeGesture);
    connect(gesture_list_item, &GestureListItem::delete_gesture, this,
            &GestureListView::delete_list_item);
}

void GestureListView::delete_list_item() {
    GestureListItem* list_item = qobject_cast<GestureListItem*>(sender());
    list_layout->removeWidget(list_item);
    delete list_item;
}
}  // namespace jesture
