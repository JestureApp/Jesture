#include "jesture/main_window.h"

namespace jesture {

MainWindow::MainWindow(Camera* camera, QWidget* parent) : QMainWindow(parent) {
    // auto content = new QWidget(this);
    // auto content_layout = new QStackedLayout(content);
    // content_layout->setStackingMode(QStackedLayout::StackAll);

    // content->setLayout(content_layout);

    pipeline_view = new PipelineView(camera, this);
    // content_layout->addWidget(pipeline_view);

    setCentralWidget(pipeline_view);
}

void MainWindow::drawLandmarks(std::vector<Landmarks> landmarks) {
    pipeline_view->drawLandmarks(landmarks);
}

}  // namespace jesture