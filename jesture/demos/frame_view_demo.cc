#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include <iostream>

#include "jesture/components/frame_view.h"
#include "jesture/jesturepipe/controller.h"
#include "jesture/jesturepipe/settings.h"
#include "tools/cpp/runfiles/runfiles.h"

using namespace jesture;

class MainWindow : public QMainWindow {
   public:
    MainWindow(JesturePipeInit init) noexcept {
        FrameView *frame_view = new FrameView(this);
        controller = new JesturePipeController(init, this);

        setCentralWidget(frame_view);

        QObject::connect(controller, &JesturePipeController::frameReady,
                         frame_view, &FrameView::setFrame);

        JesturePipeSettings settings{
            .camera_index = 0,
            .mode = 1,
            .num_hands = 2,
        };

        controller->Start(settings);

        setWindowTitle("Hello World");
    }

    void closeEvent(QCloseEvent *event) {
        if (controller) controller->Stop();
    }

   private:
    JesturePipeController *controller;
};

using bazel::tools::cpp::runfiles::Runfiles;

JesturePipeInit getInit(Runfiles *runfiles) {
    std::string palm_model_full_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/palm_detection/"
        "palm_detection_full.tflite");

    qDebug() << "Using palm model full path: "
             << QString::fromStdString(palm_model_full_path);

    std::string palm_model_lite_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/palm_detection/"
        "palm_detection_lite.tflite");

    qDebug() << "Using palm model lite path: "
             << QString::fromStdString(palm_model_full_path);

    std::string landmark_model_full_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_full.tflite");

    qDebug() << "Using landmark model full path: "
             << QString::fromStdString(landmark_model_full_path);

    std::string landmark_model_lite_path = runfiles->Rlocation(
        "mediapipe/mediapipe/modules/hand_landmark/hand_landmark_lite.tflite");

    qDebug() << "Using landmark model lite path: "
             << QString::fromStdString(landmark_model_lite_path);

    return JesturePipeInit{palm_model_full_path, palm_model_lite_path,
                           landmark_model_full_path, landmark_model_lite_path};
}

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);

    std::string error;
    Runfiles *runfiles = Runfiles::Create(argv[0], &error);

    if (runfiles == nullptr) {
        std::cout << error << std::endl;

        return 1;
    }

    JesturePipeInit init = getInit(runfiles);

    delete runfiles;

    QApplication app(argc, argv);
    app.setApplicationName("Frame View Demo");
    app.setOrganizationName("jesture");

    MainWindow main_win(init);

    main_win.show();

    return app.exec();
}