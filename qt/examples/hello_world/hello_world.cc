#include <QtQuick/QtQuick>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char *argv[]) {
    // Get path to hello_world.qml
    std::string error;
    std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));

    if (runfiles == nullptr) {
        std::cout << error << std::endl;

        return 1;
    }

    QString hello_world_qml_path = QString::fromStdString(
        runfiles->Rlocation("jesture/qt/examples/hello_world/hello_world.qml"));

    QGuiApplication app(argc, argv);
    QQuickView view;

    view.setSource(QUrl(hello_world_qml_path));
    view.show();

    return app.exec();
}