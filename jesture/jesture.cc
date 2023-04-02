#include <QtCore>
#include <QtWidgets>
#include <iostream>

#include "glog/logging.h"
#include "jesture/main_window.h"
#include "jesture/resource_manager.h"

using namespace jesture;

void setupApp(QApplication *app);
void setupMainWindow(MainWindow *window, QApplication *app,
                     ResourceManager *resourceManager);

int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);

    ResourceManager resourceManager;

    QApplication app(argc, argv);
    setupApp(&app);

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

void setupApp(QApplication *app) { app->setApplicationName("Jesture"); }

void setupMainWindow(MainWindow *window, QApplication *app,
                     ResourceManager *resourceManager) {
    QObject::connect(window, &MainWindow::quit, app, &QApplication::quit);

    window->setFixedSize(1280, 720);

    window->setWindowIcon(resourceManager->applicationWindowIcon());
}