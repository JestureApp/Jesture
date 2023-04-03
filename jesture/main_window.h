#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets>

#include "jesture/managers/camera.h"

namespace jesture {

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(Camera* camera, QWidget* parent = nullptr);

   signals:
    void quit();
};

}  // namespace jesture

#endif  // JESTURE_MAIN_WINDOW_H