#include "jesture/components/gesture_list_item.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

namespace jesture {
GestureListItem::GestureListItem(int id, Gesture gesture, Action* action,
                                 QIcon cross_icon, QWidget* parent)
    : QWidget(parent), id(id), gesture(gesture), action(action) {
    auto layout = new QHBoxLayout(this);

    auto name = new QString(gesture.name.c_str());
    auto label = new QLabel(*name, this);
    auto button_group = new QButtonGroup(this);
    mouse_grab_button = new QRadioButton("Mouse Grab", this);
    mouse_release_button = new QRadioButton("Mouse Release", this);
    keyboard_action_button = new QRadioButton("Keyboard Action", this);
    keyboard_action_input = new QKeySequenceEdit(this);
    auto delete_button = new QPushButton(cross_icon, "", this);

    button_group->addButton(mouse_grab_button);
    button_group->addButton(mouse_release_button);
    button_group->addButton(keyboard_action_button);
    keyboard_action_button->setChecked(true);
    connect(button_group, &QButtonGroup::buttonReleased, this,
            &GestureListItem::disable_key_input);

    layout->addWidget(label);
    layout->addWidget(mouse_grab_button);
    layout->addWidget(mouse_release_button);
    layout->addWidget(keyboard_action_button);
    layout->addWidget(keyboard_action_input);
    layout->addWidget(delete_button);
}

void GestureListItem::disable_key_input(QAbstractButton* button) {
    if (button == keyboard_action_button) {
        keyboard_action_input->setEnabled(true);
    } else {
        keyboard_action_input->setEnabled(false);
    }
}
}  // namespace jesture
