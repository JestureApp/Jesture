#ifndef JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H
#define JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H

#include <QWidget>

namespace jesture {

class GestureListView : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListView(QWidget* parent = nullptr);

   private:
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H