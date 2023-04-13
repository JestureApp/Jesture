#ifndef JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H
#define JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H

#include <QComboBox>
#include <QIcon>
#include <QKeySequenceEdit>
#include <QWidget>

#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"

namespace jesture {

class GestureListItem : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListItem(int id, Gesture gesture, ActionsList action,
                             QIcon cross_icon, QWidget* parent = nullptr);

   signals:
    void delete_gesture(int id);
    void update_action(int id, ActionsList action);

   private slots:
    void delete_this_item();
    void handle_action_type(int index);
    void propogate_action();

   private:
    jesturepipe::CursorControl get_cursor_control();
    Action get_action();
    void initialize_fields(ActionsList action);

    int id;
    Gesture gesture;
    QComboBox* cursor_combo;
    QComboBox* action_combo;
    QComboBox* mouse_combo;
    QKeySequenceEdit* keyboard_action_input;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H