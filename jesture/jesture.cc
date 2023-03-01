#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>

#include "config_manager.h"
#include "jesture/jesturepipe/controller.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"
#include "main_window.h"
#include "tools/cpp/runfiles/runfiles.h"

/*
Notes
QScrollArea* scroll_area = new QScrollArea;
scroll_area->setFrameShape(QFrame::NoFrame);
scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
scroll_area->verticalScrollBar()->setStyleSheet("QScrollBar:vertical
{width: 20px;}"); scroll_area->setWidget(content);

QVBoxLayout* scroll_area_layout = new QVBoxLayout;
scroll_area_layout->setContentsMargins(0, 0, 0, 0);
scroll_area_layout->addWidget(scroll_area);

setLayout(scroll_area_layout);
*/

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
    google::InitGoogleLogging(argv[0]);

    QApplication app(argc, argv);
    app.setApplicationName("Jesture");

    auto app_icon = new QIcon("icons/settings.svg");
    app.setWindowIcon(*app_icon);

    auto config_manager = new ConfigManager();
    config_manager->connect(&app, &QApplication::aboutToQuit, config_manager,
                            &ConfigManager::save);

    std::string error;
    Runfiles *runfiles = Runfiles::Create(argv[0], &error);

    if (runfiles == nullptr) {
        std::cout << "Error: " << error << std::endl;
        return 1;
    }

    auto jesturepipe_controller =
        new JesturePipeController(getInit(runfiles), &app);
    QObject::connect(&app, &QApplication::aboutToQuit, jesturepipe_controller,
                     &JesturePipeController::Stop);

    delete runfiles;

    JesturePipeSettings settings{
        .camera_index = 0,
        .mode = 1,
    };

    jesturepipe_controller->Start(settings);

    jesturepipe::Gesture testGesture(0);

    testGesture.frames.push_back(jesturepipe::GestureFrame(90, 90, 90, 90, 90));

    jesturepipe_controller->addGesture(testGesture);

    auto window = new MainWindow(jesturepipe_controller);
    window->connect(window, &MainWindow::quit, &app, &QApplication::quit);
    window->setFixedSize(1280, 720);
    window->show();

    QObject::connect(
        jesturepipe_controller, &JesturePipeController::gestureRecognizer,
        [](int id) { qInfo() << "recognized gesture with id" << id; });

    /*QObject::connect(jesturepipe_controller,
                     &JesturePipeController::gestureRecorded,
                     [](jesturepipe::Gesture gesture) {
                         qInfo() << "Got recorded gesture with"
                                 << gesture.frames.size() << "frames";
                     });*/

    return app.exec();
}