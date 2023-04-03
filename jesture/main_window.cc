#include "jesture/main_window.h"

namespace jesture {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto content = new QWidget(this);
    auto content_layout = new QStackedLayout(content);

    content->setLayout(content_layout);

    setCentralWidget(content);
}

}  // namespace jesture