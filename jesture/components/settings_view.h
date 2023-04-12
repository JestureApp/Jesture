#ifndef JESTURE_COMPONENTS_SETTINGS_VIEW_H
#define JESTURE_COMPONENTS_SETTINGS_VIEW_H

#include <QCameraDevice>
#include <QWidget>

namespace jesture {

class SettingsView : public QWidget {
    Q_OBJECT
   public:
    explicit SettingsView(QWidget* parent = nullptr);

   signals:
    void camera_changed(const QString& camera_description);
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_SETTINGS_VIEW_H