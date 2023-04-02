#include <gflags/gflags.h>

#include <QtCore>
#include <QtWidgets/QApplication>
#include <iostream>

#include "glog/logging.h"
#include "jesture/main_window.h"
#include "jesture/resource_manager.h"
#include "jesturepipe/controller.h"

using namespace jesture;

void setupApp(QApplication *app);
void setupMainWindow(MainWindow *window, QApplication *app,
                     ResourceManager *resourceManager);

int main(int argc, char *argv[]) {
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    ResourceManager resourceManager(argv[0]);

    auto pipeline_config = JesturePipeController::makeConfig(resourceManager);

    LOG(INFO) << "Starting application";
    QApplication app(argc, argv);
    setupApp(&app);

    auto pipeline = JesturePipeController(pipeline_config, &app);

    auto window = new MainWindow();
    setupMainWindow(window, &app, &resourceManager);

    window->show();

    return app.exec();
}

void printResources() {
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
}

void setupApp(QApplication *app) {
    app->setApplicationName("Jesture");
    app->setOrganizationName("Jesture");
}

void setupMainWindow(MainWindow *window, QApplication *app,
                     ResourceManager *resourceManager) {
    QObject::connect(window, &MainWindow::quit, app, &QApplication::quit);

    window->setFixedSize(1280, 720);

    window->setWindowIcon(resourceManager->applicationWindowIcon());
}