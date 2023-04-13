#ifndef JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H
#define JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H

#include <QCheckBox>
#include <QIcon>
#include <QKeySequenceEdit>
#include <QRadioButton>
#include <QWidget>

#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"

namespace jesture {

class GestureListItem : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListItem(int id, Gesture gesture, QIcon cross_icon,
                             QWidget* parent = nullptr);

   signals:
    void delete_gesture(int id);
    void update_action(int id, ActionsList action);

   private slots:
    void delete_this_item();
    void handle_mouse_buttons(QAbstractButton* button);
    void handle_key_buttons(QAbstractButton* button);
    void handle_key_input();
    void propogate_action();

   private:
    int id;
    Gesture gesture;
    QRadioButton* no_mouse_button;
    QRadioButton* mouse_grab_button;
    QRadioButton* mouse_release_button;
    QRadioButton* mouse_toggle_button;
    QCheckBox* left_click_button;
    QCheckBox* middle_click_button;
    QCheckBox* right_click_button;
    QRadioButton* no_key_button;
    QRadioButton* key_stroke_button;
    QRadioButton* key_hold_button;
    QRadioButton* key_release_button;
    QKeySequenceEdit* keyboard_action_input;
    jesturepipe::CursorControl mouse_action;
    Action key_action;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H