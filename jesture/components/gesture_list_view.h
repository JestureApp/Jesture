#ifndef JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H
#define JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H

#include <QIcon>
#include <QList>
#include <QVBoxLayout>
#include <QWidget>

#include "jesture/components/gesture_list_item.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/managers/resources.h"

namespace jesture {

class GestureListView : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListView(Resources* resources, QWidget* parent = nullptr);

   signals:
    void record_gesture();

   public slots:
    void add_gesture(int id, Gesture gesture);

   private:
    QVBoxLayout* layout;
    QList<GestureListItem> gesture_list;
    QIcon cross_icon;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H