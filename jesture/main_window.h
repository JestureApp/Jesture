#ifndef JESTURE_MAIN_WINDOW_H
#define JESTURE_MAIN_WINDOW_H

#include <QtWidgets>

#include "jesture/components/gesture_list_view.h"
#include "jesture/components/pipeline_view.h"
#include "jesture/components/recording_review.h"
#include "jesture/components/settings_view.h"
#include "jesture/components/sidebar.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/jesturepipe/landmarks.h"
#include "jesture/managers/camera.h"
#include "jesture/managers/resources.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesture {

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(Camera* camera, Resources* resources,
                        QWidget* parent = nullptr);

   signals:
    void quit();
    void set_recording(bool on);
    void open_recorded_gesture(jesturepipe::Gesture gesture);
    void camera_changed(const QCameraDevice& device);
    int add_gesture(Gesture gesture);

   public slots:
    void drawLandmarks(std::vector<Landmarks>);
    void show_pipeline_view();
    void show_settings_view();
    void show_gesture_list_view();
    void get_recorded_gesture(jesturepipe::Gesture gesture,
                              unsigned long timestamp);

   private slots:
    void handle_recording_update(bool on);
    void handle_save_gesture(Gesture gesture);

   private:
    QStackedLayout* content_layout;
    PipelineView* pipeline_view;
    SettingsView* settings_view;
    GestureListView* gesture_list_view;
    RecordingReview* recording_review;
    SidebarItem* camera_tab;
    SidebarItem* settings_tab;
    SidebarItem* gesture_tab;
};

}  // namespace jesture

#endif  // JESTURE_MAIN_WINDOW_H