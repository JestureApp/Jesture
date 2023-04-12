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
GestureListView::GestureListView(QWidget* parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);

    auto title = new QLabel("Gesture List", this);
    layout->addWidget(title);

    auto stop_gesture = new Gesture("Stop", jesturepipe::Gesture::Stop());
    auto pause_gesture = new Gesture("Pause", jesturepipe::Gesture::Pause());
    auto next_gesture = new Gesture("Next", jesturepipe::Gesture::Next());
    auto prev_gesture = new Gesture("Prev", jesturepipe::Gesture::Prev());

    auto stop_item = new GestureListItem(stop_gesture, NULL, this);
    auto pause_item = new GestureListItem(pause_gesture, NULL, this);
    auto next_item = new GestureListItem(next_gesture, NULL, this);
    auto prev_item = new GestureListItem(prev_gesture, NULL, this);
    auto add_gesture_button = new QPushButton("Record A New Gesture", this);

    layout->addWidget(stop_item);
    layout->addWidget(pause_item);
    layout->addWidget(next_item);
    layout->addWidget(prev_item);
    layout->addWidget(add_gesture_button);
}
}  // namespace jesture
