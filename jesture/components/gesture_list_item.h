#ifndef JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H
#define JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H

#include <QKeySequenceEdit>
#include <QRadioButton>
#include <QWidget>

#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"

namespace jesture {

class GestureListItem : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListItem(Gesture* gesture, Action* action,
                             QWidget* parent = nullptr);

   private slots:
    void disable_key_input(QAbstractButton* button);

   private:
    Gesture* gesture;
    Action* action;
    QRadioButton* mouse_grab_button;
    QRadioButton* mouse_release_button;
    QRadioButton* keyboard_action_button;
    QKeySequenceEdit* keyboard_action_input;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H