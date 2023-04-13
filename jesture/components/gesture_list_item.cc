#include "jesture/components/gesture_list_item.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace jesture {
GestureListItem::GestureListItem(int id, Gesture gesture, ActionsList action,
                                 QIcon cross_icon, QWidget* parent)
    : QWidget(parent), id(id), gesture(gesture) {
    auto layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);

    auto name = new QString(gesture.name.c_str());
    auto label = new QLabel(*name, this);
    label->setWordWrap(true);

    cursor_combo = new QComboBox(this);
    cursor_combo->addItem("No Cursor Control");
    cursor_combo->addItem("Cursor Grab");
    cursor_combo->addItem("Cursor Release");
    cursor_combo->addItem("Toggle Cursor Grab");

    action_combo = new QComboBox(this);
    action_combo->addItem("No Actions");
    action_combo->addItem("Mouse Click");
    action_combo->addItem("Mouse Hold");
    action_combo->addItem("Mouse Release");
    action_combo->addItem("Key Stroke");
    action_combo->addItem("Key Hold");
    action_combo->addItem("Key Release");

    mouse_combo = new QComboBox(this);
    mouse_combo->addItem("Left Click");
    mouse_combo->addItem("Middle Click");
    mouse_combo->addItem("Right Click");

    keyboard_action_input = new QKeySequenceEdit(this);

    auto delete_button = new QPushButton(cross_icon, "", this);

    initialize_fields(action);

    connect(cursor_combo, &QComboBox::currentIndexChanged, this,
            &GestureListItem::propogate_action);
    connect(action_combo, &QComboBox::currentIndexChanged, this,
            &GestureListItem::propogate_action);
    connect(action_combo, &QComboBox::currentIndexChanged, this,
            &GestureListItem::handle_action_type);
    connect(mouse_combo, &QComboBox::currentIndexChanged, this,
            &GestureListItem::propogate_action);
    connect(keyboard_action_input, &QKeySequenceEdit::keySequenceChanged, this,
            &GestureListItem::propogate_action);
    connect(delete_button, &QPushButton::released, this,
            &GestureListItem::delete_this_item);

    layout->addWidget(label);
    layout->addWidget(cursor_combo);
    layout->addWidget(action_combo);
    layout->addWidget(mouse_combo);
    layout->addWidget(keyboard_action_input);
    layout->addWidget(delete_button);
}

void GestureListItem::delete_this_item() { delete_gesture(id); }

void GestureListItem::handle_action_type(int index) {
    if (index == 0) {
        mouse_combo->setEnabled(false);
        keyboard_action_input->setEnabled(false);
    } else if (index <= 3) {
        mouse_combo->setEnabled(true);
        keyboard_action_input->setEnabled(false);
    } else {
        mouse_combo->setEnabled(false);
        keyboard_action_input->setEnabled(true);
    }
}

jesturepipe::CursorControl GestureListItem::get_cursor_control() {
    switch (cursor_combo->currentIndex()) {
        case 0:
            return jesturepipe::CursorControl::None;
        case 1:
            return jesturepipe::CursorControl::Grab;
        case 2:
            return jesturepipe::CursorControl::Release;
        case 3:
            return jesturepipe::CursorControl::Toggle;
    }
}

Action GestureListItem::get_action() {
    switch (action_combo->currentIndex()) {
        case 0:
            return NoOp();
        case 1:
            return MouseClick(mouse_combo->currentIndex());
        case 2:
            return MousePress(mouse_combo->currentIndex());
        case 3:
            return MouseRelease(mouse_combo->currentIndex());
        case 4:
            return Keystroke(keyboard_action_input->keySequence());
        case 5:
            return KeysPress(keyboard_action_input->keySequence());
        case 6:
            return KeysRelease(keyboard_action_input->keySequence());
    }
}

void GestureListItem::initialize_fields(ActionsList action_list) {
    switch (action_list.cursor_control) {
        case jesturepipe::CursorControl::None:
            cursor_combo->setCurrentIndex(0);
            break;
        case jesturepipe::CursorControl::Grab:
            cursor_combo->setCurrentIndex(1);
            break;
        case jesturepipe::CursorControl::Release:
            cursor_combo->setCurrentIndex(2);
            break;
        case jesturepipe::CursorControl::Toggle:
            cursor_combo->setCurrentIndex(3);
            break;
    }

    if (action_list.action_list.empty()) {
        action_combo->setCurrentIndex(0);
        return;
    }

    Action action = action_list.action_list[0];
    if (absl::holds_alternative<actions::action::NoOp>(
            action.pipeline_action)) {
        action_combo->setCurrentIndex(0);
    } else if (absl::holds_alternative<actions::action::MouseClick>(
                   action.pipeline_action)) {
        action_combo->setCurrentIndex(1);
        switch (
            absl::get<actions::action::MouseClick>(action.pipeline_action)) {
            case actions::action::MouseClick::LeftClick:
                mouse_combo->setCurrentIndex(0);
                break;
            case actions::action::MouseClick::MiddleClick:
                mouse_combo->setCurrentIndex(1);
                break;
            case actions::action::MouseClick::RightClick:
                mouse_combo->setCurrentIndex(2);
                break;
        }
    } else if (absl::holds_alternative<actions::action::MousePress>(
                   action.pipeline_action)) {
        action_combo->setCurrentIndex(2);
        switch (
            absl::get<actions::action::MousePress>(action.pipeline_action)) {
            case actions::action::MousePress::LeftPress:
                mouse_combo->setCurrentIndex(0);
                break;
            case actions::action::MousePress::MiddlePress:
                mouse_combo->setCurrentIndex(1);
                break;
            case actions::action::MousePress::RightPress:
                mouse_combo->setCurrentIndex(2);
                break;
        }
    } else if (absl::holds_alternative<actions::action::MouseRelease>(
                   action.pipeline_action)) {
        action_combo->setCurrentIndex(3);
        switch (
            absl::get<actions::action::MouseRelease>(action.pipeline_action)) {
            case actions::action::MouseRelease::LeftRelease:
                mouse_combo->setCurrentIndex(0);
                break;
            case actions::action::MouseRelease::MiddleRelease:
                mouse_combo->setCurrentIndex(1);
                break;
            case actions::action::MouseRelease::RightRelease:
                mouse_combo->setCurrentIndex(2);
                break;
        }
    } else if (absl::holds_alternative<actions::action::Keystroke>(
                   action.pipeline_action)) {
        action_combo->setCurrentIndex(4);
        keyboard_action_input->setKeySequence(action.sequence);
    } else if (absl::holds_alternative<actions::action::KeysPress>(
                   action.pipeline_action)) {
        action_combo->setCurrentIndex(5);
        keyboard_action_input->setKeySequence(action.sequence);
    } else {
        action_combo->setCurrentIndex(6);
        keyboard_action_input->setKeySequence(action.sequence);
    }

    handle_action_type(action_combo->currentIndex());
}

void GestureListItem::propogate_action() {
    std::vector<Action> action_list;
    action_list.push_back(get_action());
    update_action(
        id, ActionsList{action_list, .cursor_control = get_cursor_control()});
}
}  // namespace jesture
