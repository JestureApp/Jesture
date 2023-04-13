#ifndef JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H
#define JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H

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
    explicit GestureListItem(int id, Gesture gesture, Action* action,
                             QIcon cross_icon, QWidget* parent = nullptr);

   signals:
    void delete_gesture(int id);

   private slots:
    void disable_key_input(QAbstractButton* button);
    void delete_this_item();

   private:
    int id;
    Gesture gesture;
    Action* action;
    QRadioButton* no_key_button;
    QKeySequenceEdit* keyboard_action_input;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_ITEM_H