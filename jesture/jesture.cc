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

// FLAGS
DEFINE_bool(silent, true, "Do not log any information to stderr");
DEFINE_bool(config, true, "Whether or not to load config");
DEFINE_bool(reset, true, "Whether or not to set config back to defaults");

using namespace jesture;

void setupApp(QApplication *app);
void setupConfig(Config *config, QApplication *app);
void setupCamera(Camera *camera, Config *config);
void setupPipeline(JesturePipeController *pipeline, Config *config);
void setupMainWindow(MainWindow *window, QApplication *app,
                     JesturePipeController *pipeline,
                     Resources *resourceManager, Config *config);

void defaultFlagValues() {
    FLAGS_silent = false;
    FLAGS_config = true;
    FLAGS_reset = false;
}

int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);

    defaultFlagValues();
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    FLAGS_alsologtostderr = FLAGS_silent ? 0 : 1;
    Resources resources(argv[0]);

    auto pipeline_config = JesturePipeController::makeConfig(resources);

    LOG(INFO) << "Starting application";
    QApplication app(argc, argv);
    setupApp(&app);

    auto config = new Config(&app);
    auto camera = new Camera(&app);
    auto pipeline = new JesturePipeController(camera, pipeline_config, &app);
    setupConfig(config, &app);
    setupPipeline(pipeline, config);
    setupCamera(camera, config);

    auto window = new MainWindow(camera, &resources, config);
    setupMainWindow(window, &app, pipeline, &resources, config);

    window->show();

    pipeline->start(false);

    return app.exec();
}

void printResources() {
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
}

void setupApp(QApplication *app) { app->setApplicationName("Jesture"); }

void setupConfig(Config *config, QApplication *app) {
    config->init(FLAGS_config && !FLAGS_reset);

    if (FLAGS_config || FLAGS_reset)
        QObject::connect(app, &QCoreApplication::aboutToQuit, config,
                         &Config::save);
}

void setupCamera(Camera *camera, Config *config) {
    camera->setDevice(config->cameraDevice());

    QObject::connect(config, &Config::cameraDeviceChanged, camera,
                     &Camera::setDevice);
}

void setupPipeline(JesturePipeController *pipeline, Config *config) {
    for (const auto &[id, gesture] : config->getGestures()) {
        pipeline->setGesture(id, gesture);
    }

    for (const auto &[id, action] : config->getActions()) {
        pipeline->setAction(id, action);
    }

    QObject::connect(config, &Config::gestureChanged, pipeline,
                     &JesturePipeController::setGesture);

    QObject::connect(config, &Config::gestureRemoved, pipeline,
                     &JesturePipeController::removeGesture);

    QObject::connect(config, &Config::gesturesCleared, pipeline,
                     &JesturePipeController::clearGestures);

    QObject::connect(config, &Config::actionChanged, pipeline,
                     &JesturePipeController::setAction);

    QObject::connect(config, &Config::actionRemoved, pipeline,
                     &JesturePipeController::removeAction);

    QObject::connect(config, &Config::pipelineSettingsChanged, pipeline,
                     &JesturePipeController::restart);
}

void setupMainWindow(MainWindow *window, QApplication *app,
                     JesturePipeController *pipeline,
                     Resources *resourceManager, Config *config) {
    // Application connections
    QObject::connect(window, &MainWindow::quit, app, &QApplication::quit);

    // Pipeline connections
    QObject::connect(
        pipeline, &JesturePipeController::landmarksReady, window,
        [window](std::vector<Landmarks> landmarks, unsigned long timestamp) {
            window->drawLandmarks(landmarks);
        });
    QObject::connect(window, &MainWindow::set_recording, pipeline,
                     &JesturePipeController::setRecording);
    QObject::connect(pipeline, &JesturePipeController::gestureRecorded, window,
                     &MainWindow::get_recorded_gesture);

    window->resize(1280, 720);
    window->setWindowIcon(resourceManager->application_icon());
    window->setWindowTitle("Jesture");
}