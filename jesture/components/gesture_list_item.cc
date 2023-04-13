#include "jesture/components/gesture_list_item.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>

namespace jesture {
GestureListItem::GestureListItem(int id, Gesture gesture, QIcon cross_icon,
                                 QWidget* parent)
    : QWidget(parent), id(id), gesture(gesture) {
    auto layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignTop);

    auto name = new QString(gesture.name.c_str());
    auto label = new QLabel(*name, this);

    label->setWordWrap(true);

    layout->addWidget(label, 0, 0, 4, 1);

    no_mouse_button = new QRadioButton("No Mouse Action", this);
    mouse_grab_button = new QRadioButton("Mouse Grab", this);
    mouse_release_button = new QRadioButton("Mouse Release", this);
    mouse_toggle_button = new QRadioButton("Toggle Mouse Grab", this);

    auto mouse_button_group = new QButtonGroup(this);
    mouse_button_group->addButton(no_mouse_button);
    mouse_button_group->addButton(mouse_grab_button);
    mouse_button_group->addButton(mouse_release_button);
    mouse_button_group->addButton(mouse_toggle_button);

    connect(mouse_button_group, &QButtonGroup::buttonReleased, this,
            &GestureListItem::handle_mouse_buttons);

    layout->addWidget(no_mouse_button, 0, 1);
    layout->addWidget(mouse_grab_button, 1, 1);
    layout->addWidget(mouse_release_button, 2, 1);
    layout->addWidget(mouse_toggle_button, 3, 1);

    left_click_button = new QCheckBox("Left Click", this);
    middle_click_button = new QCheckBox("Middle Click", this);
    right_click_button = new QCheckBox("Right Click", this);

    layout->addWidget(left_click_button, 0, 2);
    layout->addWidget(middle_click_button, 1, 2);
    layout->addWidget(right_click_button, 2, 2);

    no_key_button = new QRadioButton("No Keyboard Action", this);
    key_stroke_button = new QRadioButton("Key Stroke", this);
    key_hold_button = new QRadioButton("Key Hold", this);
    key_release_button = new QRadioButton("Key Release", this);

    auto key_button_group = new QButtonGroup(this);
    key_button_group->addButton(no_key_button);
    key_button_group->addButton(key_stroke_button);
    key_button_group->addButton(key_hold_button);
    key_button_group->addButton(key_release_button);

    connect(key_button_group, &QButtonGroup::buttonReleased, this,
            &GestureListItem::handle_key_buttons);

    no_key_button->setChecked(true);

    layout->addWidget(no_key_button, 0, 3);
    layout->addWidget(key_stroke_button, 1, 3);
    layout->addWidget(key_hold_button, 2, 3);
    layout->addWidget(key_release_button, 3, 3);

    keyboard_action_input = new QKeySequenceEdit(this);

    connect(keyboard_action_input, &QKeySequenceEdit::keySequenceChanged, this,
            &GestureListItem::propogate_action);

    layout->addWidget(keyboard_action_input, 0, 4, 4, 1);

    auto delete_button = new QPushButton(cross_icon, "", this);

    connect(delete_button, &QPushButton::released, this,
            &GestureListItem::delete_this_item);

    layout->addWidget(delete_button, 0, 5, 4, 1);
}

void GestureListItem::delete_this_item() { delete_gesture(id); }

void GestureListItem::handle_mouse_buttons(QAbstractButton* button) {
    if (button == no_mouse_button) {
        mouse_action = jesturepipe::CursorControl::None;
    } else if (button == mouse_grab_button) {
        mouse_action = jesturepipe::CursorControl::Grab;
    } else if (button == mouse_release_button) {
        mouse_action = jesturepipe::CursorControl::Release;
    } else if (button == mouse_toggle_button) {
        mouse_action = jesturepipe::CursorControl::Toggle;
    }

    propogate_action();
}

void GestureListItem::handle_key_buttons(QAbstractButton* button) {
    if (button == no_key_button) {
        keyboard_action_input->setEnabled(false);
    } else {
        keyboard_action_input->setEnabled(true);
    }

    if (button == no_key_button) {
        key_action = NoOp();
    } else if (button == key_stroke_button) {
        key_action = Keystroke(keyboard_action_input->keySequence());
    } else if (button == key_hold_button) {
        key_action = KeysPress(keyboard_action_input->keySequence());
    } else if (button == key_release_button) {
        key_action = KeysRelease(keyboard_action_input->keySequence());
    }

    propogate_action();
}

void GestureListItem::propogate_action() {
    std::vector<Action> action_list;
    action_list.push_back(key_action);
    update_action(id, ActionsList{action_list, .cursor_control = mouse_action});
}
}  // namespace jesture
