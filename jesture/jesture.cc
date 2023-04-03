#include <gflags/gflags.h>

#include <QtCore>
#include <QtWidgets/QApplication>
#include <iostream>

#include "glog/logging.h"
#include "jesture/main_window.h"
#include "jesture/managers/camera.h"
#include "jesture/managers/config.h"
#include "jesture/managers/resources.h"
#include "jesturepipe/controller.h"

using namespace jesture;

void setupApp(QApplication *app);
void setupConfig(Config *config, QApplication *app);
void setupMainWindow(MainWindow *window, QApplication *app,
                     Resources *resourceManager);

int main(int argc, char *argv[]) {
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    Resources resources(argv[0]);

    auto pipeline_config = JesturePipeController::makeConfig(resources);

    LOG(INFO) << "Starting application";
    QApplication app(argc, argv);
    setupApp(&app);

    auto config = new Config(&app);
    setupConfig(config, &app);

    auto camera = new Camera(&app);

    auto pipeline = JesturePipeController(pipeline_config, &app);

    auto window = new MainWindow();
    setupMainWindow(window, &app, &resources);

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

void setupConfig(Config *config, QApplication *app) {
    QObject::connect(app, &QCoreApplication::aboutToQuit, config,
                     &Config::save);
}

void setupMainWindow(MainWindow *window, QApplication *app,
                     Resources *resourceManager) {
    QObject::connect(window, &MainWindow::quit, app, &QApplication::quit);

    window->setFixedSize(1280, 720);

    window->setWindowIcon(resourceManager->applicationWindowIcon());
}