#include "jesture/main_window.h"

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

    sidebar->createItem(resources->settingsIcon(), "Settings");

    auto content = new QWidget(main);
    main_layout->addWidget(content);

    auto content_layout = new QStackedLayout(content);
    content_layout->setSpacing(0);
    content_layout->setContentsMargins(0, 0, 0, 0);
    content->setLayout(content_layout);

    pipeline_view = new PipelineView(camera, this);
    pipeline_view->setContentsMargins(0, 0, 0, 0);
    content_layout->addWidget(pipeline_view);

    setCentralWidget(main);
}

void MainWindow::drawLandmarks(std::vector<Landmarks> landmarks) {
    pipeline_view->drawLandmarks(landmarks);
}

}  // namespace jesture