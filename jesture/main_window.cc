#include "jesture/main_window.h"

#include "jesture/components/pipeline_view.h"

namespace jesture {

MainWindow::MainWindow(Camera* camera, QWidget* parent) : QMainWindow(parent) {
    // auto content = new QWidget(this);
    // auto content_layout = new QStackedLayout(content);
    // content_layout->setStackingMode(QStackedLayout::StackAll);

    // content->setLayout(content_layout);

    auto pipeline_view = new PipelineView(camera, this);
    // content_layout->addWidget(pipeline_view);

    setCentralWidget(pipeline_view);
}

}  // namespace jesture