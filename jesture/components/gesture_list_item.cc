#include "jesture/components/gesture_list_item.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

namespace jesture {
GestureListItem::GestureListItem(int id, Gesture gesture, Action* action,
                                 QIcon cross_icon, QWidget* parent)
    : QWidget(parent), id(id), gesture(gesture), action(action) {
    auto layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignTop);

    auto name = new QString(gesture.name.c_str());
    auto label = new QLabel(*name, this);

    label->setWordWrap(true);

    layout->addWidget(label, 0, 0, 4, 1);

    auto no_mouse_button = new QRadioButton("No Mouse Action", this);
    auto mouse_grab_button = new QRadioButton("Mouse Grab", this);
    auto mouse_release_button = new QRadioButton("Mouse Release", this);
    auto mouse_toggle_button = new QRadioButton("Toggle Mouse Grab", this);

    auto mouse_button_group = new QButtonGroup(this);
    mouse_button_group->addButton(no_mouse_button);
    mouse_button_group->addButton(mouse_grab_button);
    mouse_button_group->addButton(mouse_release_button);
    mouse_button_group->addButton(mouse_toggle_button);

    layout->addWidget(no_mouse_button, 0, 1);
    layout->addWidget(mouse_grab_button, 1, 1);
    layout->addWidget(mouse_release_button, 2, 1);
    layout->addWidget(mouse_toggle_button, 3, 1);

    auto left_click_button = new QCheckBox("Left Click", this);
    auto middle_click_button = new QCheckBox("Middle Click", this);
    auto right_click_button = new QCheckBox("Right Click", this);

    layout->addWidget(left_click_button, 0, 2);
    layout->addWidget(middle_click_button, 1, 2);
    layout->addWidget(right_click_button, 2, 2);

    no_key_button = new QRadioButton("No Keyboard Action", this);
    auto key_stroke_button = new QRadioButton("Key Stroke", this);
    auto key_hold_button = new QRadioButton("Key Hold", this);
    auto key_release_button = new QRadioButton("Key Release", this);

    auto key_button_group = new QButtonGroup(this);
    key_button_group->addButton(no_key_button);
    key_button_group->addButton(key_stroke_button);
    key_button_group->addButton(key_hold_button);
    key_button_group->addButton(key_release_button);

    connect(key_button_group, &QButtonGroup::buttonReleased, this,
            &GestureListItem::disable_key_input);

    layout->addWidget(no_key_button, 0, 3);
    layout->addWidget(key_stroke_button, 1, 3);
    layout->addWidget(key_hold_button, 2, 3);
    layout->addWidget(key_release_button, 3, 3);

    keyboard_action_input = new QKeySequenceEdit(this);

    layout->addWidget(keyboard_action_input, 0, 4, 4, 1);

    auto delete_button = new QPushButton(cross_icon, "", this);

    connect(delete_button, &QPushButton::released, this,
            &GestureListItem::delete_this_item);

    layout->addWidget(delete_button, 0, 5, 4, 1);
}

void GestureListItem::disable_key_input(QAbstractButton* button) {
    if (button == no_key_button) {
        keyboard_action_input->setEnabled(true);
    } else {
        keyboard_action_input->setEnabled(false);
    }
}

void GestureListItem::delete_this_item() { delete_gesture(id); }
}  // namespace jesture
