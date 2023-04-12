#ifndef JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H
#define JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H

#include <QWidget>

#include "jesture/managers/resources.h"

namespace jesture {

class GestureListView : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListView(Resources* resources, QWidget* parent = nullptr);

   signals:
    void add_gesture();
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H