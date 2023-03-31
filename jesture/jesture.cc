#include <QtCore>
#include <QtWidgets>
#include <iostream>

#include "glog/logging.h"
#include "jesture/main_window.h"

using namespace jesture;

void setupApp(QApplication *app);
void setupMainWindow(MainWindow *window, QApplication *app);

int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);

    QApplication app(argc, argv);
    setupApp(&app);

    auto window = new MainWindow();
    setupMainWindow(window, &app);

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

void setupMainWindow(MainWindow *window, QApplication *app) {
    QObject::connect(window, &MainWindow::quit, app, &QApplication::quit);

    window->setFixedSize(1280, 720);

    QImageReader reader(":/jesture.png");

    qDebug() << QImageReader::supportedImageFormats();

    QImage image = reader.read();

    if (image.isNull()) {
        qDebug() << reader.errorString();
        qFatal("failed to read icon");
    }

    QIcon icon(QPixmap::fromImage(image));

    assert(!icon.isNull());

    window->setWindowIcon(icon);
}