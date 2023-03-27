#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>

#include "config_manager.h"
#include "jesture/jesturepipe/controller.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"
#include "main_window.h"
#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;
using namespace jesture;

JesturePipeInit getInit(Runfiles *runfiles) {
    std::string palm_model_full_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/palm_detection/"
        "palm_detection_full.tflite");

    std::string palm_model_lite_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/palm_detection/"
        "palm_detection_lite.tflite");

    std::string landmark_model_full_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_full.tflite");

    std::string landmark_model_lite_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_lite.tflite");

    return JesturePipeInit{palm_model_full_path, palm_model_lite_path,
                           landmark_model_full_path, landmark_model_lite_path};
}

int main(int argc, char **argv) {
    // Mediapipe/Jesturepipe logging
    google::InitGoogleLogging(argv[0]);

    // Create app
    QApplication app(argc, argv);
    app.setApplicationName("Jesture");

    // Set app icon
    auto app_icon = new QIcon("icons/settings.svg");
    app.setWindowIcon(*app_icon);

    // Setup runfiles for JesturePipe tflite files
    std::string error;
    auto runfiles = Runfiles::Create(argv[0], &error);
    if (runfiles == nullptr) {
        std::cout << "Error: " << error << std::endl;
        return 1;
    }

    // Create app components
    auto config_manager = new ConfigManager();
    auto jesturepipe_controller =
        new JesturePipeController(getInit(runfiles), &app);
    auto window = new MainWindow(config_manager->get_settings(),
                                 config_manager->get_gestures());

    // Clear runfiles memory
    delete runfiles;

    // Qt Signal-Slot Connections
    jesturepipe_controller->connect(&app, &QApplication::aboutToQuit,
                                    jesturepipe_controller,
                                    &JesturePipeController::Stop);
    // jesturepipe_controller->connect(
    //     jesturepipe_controller, &JesturePipeController::gestureRecorded,
    //     jesturepipe_controller, &JesturePipeController::addGesture);
    jesturepipe_controller->connect(jesturepipe_controller,
                                    &JesturePipeController::gestureRecorded,
                                    window, &MainWindow::add_gesture);
    config_manager->connect(&app, &QApplication::aboutToQuit, config_manager,
                            &ConfigManager::save);
    config_manager->connect(
        config_manager, &ConfigManager::settings_to_controller,
        jesturepipe_controller, &JesturePipeController::updateSettings);
    window->connect(window, &MainWindow::quit, &app, &QApplication::quit);
    window->connect(window, &MainWindow::toggle_recording,
                    jesturepipe_controller,
                    &JesturePipeController::toggleRecording);
    window->connect(jesturepipe_controller, &JesturePipeController::frameReady,
                    window, &MainWindow::new_camera_frame);
    window->connect(window, &MainWindow::update_camera_setting, config_manager,
                    &ConfigManager::update_camera_setting);

    // Initialize app components
    jesturepipe_controller->Start(config_manager->get_settings());
    int i = 0;
    for (auto gesture : config_manager->get_gestures()) {
        jesturepipe_controller->addGesture(i, gesture);
        i++;
    }
    window->setFixedSize(1280, 720);
    window->show();

    // Debug logging to detect gestures emitted
    QObject::connect(
        jesturepipe_controller, &JesturePipeController::gestureRecognizer,
        [](int id) { qInfo() << "recognized gesture with id" << id; });
    QObject::connect(jesturepipe_controller,
                     &JesturePipeController::gestureRecorded,
                     [](jesturepipe::Gesture gesture) {
                         qInfo() << "Got recorded gesture with"
                                 << gesture.frames->size() << "frames";
                     });

    return app.exec();
}