#include "jesture/main_window.h"

namespace jesture {

MainWindow::MainWindow(Camera* camera, Resources* resources, Config* config,
                       QWidget* parent)
    : QMainWindow(parent) {
    auto main = new QWidget(this);

    auto main_layout = new QHBoxLayout(main);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main->setLayout(main_layout);

    auto sidebar = new Sidebar(this);
    main_layout->addWidget(sidebar);

    camera_tab = sidebar->create_item(resources->show_icon(), "Camera View");
    settings_tab = sidebar->create_item(resources->settings_icon(), "Settings");
    gesture_tab =
        sidebar->create_item(resources->add_element_icon(), "Gesture List");

    connect(camera_tab, &SidebarItem::released, this,
            &MainWindow::show_pipeline_view);
    connect(settings_tab, &SidebarItem::released, this,
            &MainWindow::show_settings_view);
    connect(gesture_tab, &SidebarItem::released, this,
            &MainWindow::show_gesture_list_view);

    auto content = new QWidget(main);
    main_layout->addWidget(content);

    content_layout = new QStackedLayout(content);
    content_layout->setSpacing(0);
    content_layout->setContentsMargins(0, 0, 0, 0);
    content->setLayout(content_layout);

    pipeline_view = new PipelineView(camera, this);
    pipeline_view->setContentsMargins(0, 0, 0, 0);
    content_layout->addWidget(pipeline_view);

    settings_view = new SettingsView(config, this);
    content_layout->addWidget(settings_view);

    gesture_list_view = new GestureListView(resources, config, this);
    content_layout->addWidget(gesture_list_view);

    connect(gesture_list_view, &GestureListView::record_gesture, camera_tab,
            &SidebarItem::released);
    connect(gesture_list_view, &GestureListView::record_gesture, pipeline_view,
            &PipelineView::show_recording);
    connect(pipeline_view, &PipelineView::set_recording, this,
            &MainWindow::handle_recording_update);

    recording_review = new RecordingReview(this);
    content_layout->addWidget(recording_review);

    connect(this, &MainWindow::open_recorded_gesture, recording_review,
            &RecordingReview::set_gesture);
    connect(recording_review, &RecordingReview::cancel, gesture_tab,
            &SidebarItem::released);
    connect(recording_review, &RecordingReview::save_gesture, gesture_tab,
            &SidebarItem::released);
    connect(recording_review, &RecordingReview::save_gesture, this,
            &MainWindow::handle_save_gesture);
    connect(this, &MainWindow::add_gesture, config, &Config::addGesture);

    setCentralWidget(main);
}

void MainWindow::drawLandmarks(std::vector<Landmarks> landmarks) {
    pipeline_view->drawLandmarks(landmarks);
}

void MainWindow::show_pipeline_view() {
    content_layout->setCurrentWidget(pipeline_view);
}

void MainWindow::show_settings_view() {
    content_layout->setCurrentWidget(settings_view);
}

void MainWindow::show_gesture_list_view() {
    content_layout->setCurrentWidget(gesture_list_view);
}

void MainWindow::handle_recording_update(bool on) {
    if (!on) {
        gesture_tab->released();
    }
    set_recording(on);
}

void MainWindow::get_recorded_gesture(jesturepipe::Gesture gesture,
                                      unsigned long timestamp) {
    content_layout->setCurrentWidget(recording_review);
    gesture_tab->setEnabled(true);
    open_recorded_gesture(gesture);
}

void MainWindow::handle_save_gesture(Gesture gesture) {
    int gesture_id = add_gesture(gesture);
    gesture_list_view->add_gesture(gesture_id, gesture);
}

}  // namespace jesture