#include "jesture/main_window.h"

#include "jesture/components/sidebar.h"

namespace jesture {

MainWindow::MainWindow(Camera* camera, Resources* resources, QWidget* parent)
    : QMainWindow(parent) {
    auto main = new QWidget(this);

    auto main_layout = new QHBoxLayout(main);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main->setLayout(main_layout);

    auto sidebar = new Sidebar(this);
    main_layout->addWidget(sidebar);

    auto camera_tab =
        sidebar->create_item(resources->show_icon(), "Camera View");
    auto settings_tab =
        sidebar->create_item(resources->settings_icon(), "Settings");
    auto gesture_tab =
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

    settings_view = new SettingsView(this);
    content_layout->addWidget(settings_view);

    gesture_list_view = new GestureListView(resources, this);
    content_layout->addWidget(gesture_list_view);

    connect(gesture_list_view, &GestureListView::add_gesture, camera_tab,
            &SidebarItem::released);
    connect(gesture_list_view, &GestureListView::add_gesture, pipeline_view,
            &PipelineView::show_recording);

    recording_review = new RecordingReview(this);
    content_layout->addWidget(recording_review);

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

void MainWindow::show_recording_review() {
    content_layout->setCurrentWidget(recording_review);
}

}  // namespace jesture