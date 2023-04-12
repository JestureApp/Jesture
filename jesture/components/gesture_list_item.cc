#include "jesture/components/gesture_list_item.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

namespace jesture {
GestureListItem::GestureListItem(Gesture* gesture, Action* action,
                                 QWidget* parent)
    : QWidget(parent), gesture(gesture), action(action) {
    auto layout = new QHBoxLayout(this);

    auto name = new QString(gesture->name.c_str());
    auto name_input = new QLineEdit(*name, this);
    auto button_group = new QButtonGroup(this);
    mouse_grab_button = new QRadioButton("Mouse Grab", this);
    mouse_release_button = new QRadioButton("Mouse Release", this);
    keyboard_action_button = new QRadioButton("Keyboard Action", this);
    keyboard_action_input = new QKeySequenceEdit(this);
    auto delete_button = new QPushButton("Delete", this);

    button_group->addButton(mouse_grab_button);
    button_group->addButton(mouse_release_button);
    button_group->addButton(keyboard_action_button);
    keyboard_action_button->setChecked(true);
    connect(button_group, &QButtonGroup::buttonReleased, this,
            &GestureListItem::disable_key_input);

    layout->addWidget(name_input);
    layout->addWidget(mouse_grab_button);
    layout->addWidget(mouse_release_button);
    layout->addWidget(keyboard_action_button);
    layout->addWidget(keyboard_action_input);
    layout->addWidget(delete_button);
}

void GestureListItem::disable_key_input(QAbstractButton* button) {
    if (button == keyboard_action_button) {
        keyboard_action_input->setEnabled(true);
        std::cout << "Enabled!" << std::endl;
    } else {
        keyboard_action_input->setEnabled(false);
        std::cout << "Disabled!" << std::endl;
    }
}
}  // namespace jesture
