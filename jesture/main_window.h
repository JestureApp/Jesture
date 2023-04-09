#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets>

#include "jesture/components/pipeline_view.h"
#include "jesture/components/sidebar.h"
#include "jesture/jesturepipe/landmarks.h"
#include "jesture/managers/camera.h"
#include "jesture/managers/resources.h"

namespace jesture {

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(Camera* camera, Resources* resources,
                        QWidget* parent = nullptr);

   signals:
    void quit();

   public slots:
    void drawLandmarks(std::vector<Landmarks>);

   private:
    PipelineView* pipeline_view;
};

}  // namespace jesture

#endif  // JESTURE_MAIN_WINDOW_H