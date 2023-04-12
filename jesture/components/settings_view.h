#ifndef JESTURE_COMPONENTS_SETTINGS_VIEW_H
#define JESTURE_COMPONENTS_SETTINGS_VIEW_H

#include <QCameraDevice>
#include <QWidget>

#include "jesture/managers/config.h"

namespace jesture {

class SettingsView : public QWidget {
    Q_OBJECT
   public:
    explicit SettingsView(Config* config, QWidget* parent = nullptr);

   private slots:
    void combo_index_to_camera_device(int index);
    void combo_index_to_accuracy(int index);

   signals:
    void camera_changed(const QCameraDevice& device);
    void accuracy_changed(bool full);
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_SETTINGS_VIEW_H