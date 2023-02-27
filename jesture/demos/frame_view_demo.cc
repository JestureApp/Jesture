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
    MainWindow() noexcept {
        frame_view = new FrameView(this);

        setCentralWidget(frame_view);

        setWindowTitle("Hello World");
    }

    absl::Status init(JesturePipeInit init) noexcept {
        auto maybe_controller = JesturePipeController::Create(init, this);

        if (!maybe_controller.ok()) return maybe_controller.status();

        absl::Status status = absl::OkStatus();

        controller = maybe_controller.value();

        QObject::connect(controller, &JesturePipeController::frameReady,
                         frame_view, &FrameView::setFrame);

        JesturePipeSettings settings{
            .camera_index = 0,
            .mode = 1,
            .num_hands = 2,
        };

        status.Update(controller->Start(settings));

        return status;
    }

    void closeEvent(QCloseEvent *event) {
        absl::Status status = absl::OkStatus();

        if (controller) status.Update(controller->Stop());

        if (!status.ok()) {
            qInfo() << QString::fromStdString(status.ToString());
        }
    }

   private:
    JesturePipeController *controller;
    FrameView *frame_view;
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

    MainWindow main_win;

    absl::Status status = main_win.init(init);

    if (!status.ok()) {
        std::cerr << status << std::endl;
        app.exit(1);
    }

    main_win.show();

    return app.exec();
}