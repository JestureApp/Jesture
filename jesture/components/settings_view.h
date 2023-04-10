#ifndef JESTURE_COMPONENTS_SETTINGS_VIEW_H
#define JESTURE_COMPONENTS_SETTINGS_VIEW_H

#include <QGraphicsView>
#include <QWidget>

namespace jesture {

class SettingsView : public QWidget {
    Q_OBJECT
   public:
    explicit SettingsView(QWidget* parent = nullptr);

   private:
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_SETTINGS_VIEW_H