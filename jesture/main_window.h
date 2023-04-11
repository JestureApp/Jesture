#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets>

#include "jesture/components/gesture_list_view.h"
#include "jesture/components/pipeline_view.h"
#include "jesture/components/recording_review.h"
#include "jesture/components/recording_view.h"
#include "jesture/components/settings_view.h"
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
    void show_pipeline_view();
    void show_settings_view();
    void show_gesture_list_view();
    void show_recording_view();
    void show_recording_review();

   private:
    QStackedLayout* content_layout;
    PipelineView* pipeline_view;
    SettingsView* settings_view;
    GestureListView* gesture_list_view;
    RecordingView* recording_view;
    RecordingReview* recording_review;
};

}  // namespace jesture

#endif  // JESTURE_MAIN_WINDOW_H