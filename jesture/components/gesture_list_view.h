#ifndef JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H
#define JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H

#include <QIcon>
#include <QVBoxLayout>
#include <QWidget>

#include "jesture/components/gesture_list_item.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/managers/config.h"
#include "jesture/managers/resources.h"

namespace jesture {

class GestureListView : public QWidget {
    Q_OBJECT
   public:
    explicit GestureListView(Resources* resources, Config* config,
                             QWidget* parent = nullptr);

   signals:
    void record_gesture();

   public slots:
    void add_gesture(int id, Gesture gesture);
    void add_gesture(int id, Gesture gesture, ActionsList action);
    void delete_list_item();

   private:
    QVBoxLayout* list_layout;
    QIcon cross_icon;
    Config* config;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_GESTURE_LIST_VIEW_H