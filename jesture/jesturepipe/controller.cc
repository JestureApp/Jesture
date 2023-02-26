#include "jesture/jesturepipe/controller.h"

#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
using namespace std::placeholders;
const char OutputFrameStream[] = "annotated_frame";
}  // namespace

JesturePipeController::JesturePipeController(QObject *parent) noexcept
    : QObject(parent), running(false) {}

JesturePipeController::~JesturePipeController() noexcept {
    // TODO: should probably log this error.
    Stop().IgnoreError();
}

absl::StatusOr<JesturePipeController *> JesturePipeController::Create(
    JesturePipeInit init, QObject *parent) noexcept {
    JesturePipeController *controller = new JesturePipeController(parent);

    MP_RETURN_IF_ERROR(jesturepipe::jesturepipe_graph(
        &controller->graph, init.palm_model_full_path,
        init.palm_model_lite_path, init.landmark_model_full_path,
        init.landmark_model_lite_path));

    return controller;
}

absl::Status JesturePipeController::Start(
    JesturePipeSettings settings) noexcept {
    if (running) return absl::OkStatus();

    const std::map<std::string, mediapipe::Packet> side_packets = {
        {"camera_index", mediapipe::MakePacket<int>(settings.camera_index)
                             .At(mediapipe::Timestamp(0))},
        {"mode",
         mediapipe::MakePacket<int>(settings.mode).At(mediapipe::Timestamp(0))},
        {"num_hands", mediapipe::MakePacket<int>(settings.num_hands)
                          .At(mediapipe::Timestamp(0))}};

    MP_RETURN_IF_ERROR(graph.StartRun(side_packets));

    MP_RETURN_IF_ERROR(graph.ObserveOutputStream(
        OutputFrameStream,
        std::bind(&JesturePipeController::onFrame, this, _1)));

    running = true;

    return absl::OkStatus();
}

absl::Status JesturePipeController::Stop() noexcept {
    if (!running) return absl::OkStatus();

    MP_RETURN_IF_ERROR(graph.CloseAllPacketSources());

    MP_RETURN_IF_ERROR(graph.WaitUntilDone());

    running = false;

    return absl::OkStatus();
}

absl::Status JesturePipeController::onFrame(
    mediapipe::Packet frame_packet) noexcept {
    // CHECKME: Image manipulation is expensive. Maybe there is a way to check
    // if anyone is listening to the `frameReady` slot.

    auto &output_frame = frame_packet.Get<mediapipe::ImageFrame>();

    cv::Mat mat = mediapipe::formats::MatView(&output_frame);

    QImage img =
        QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

    emit frameReady(img);

    return absl::OkStatus();
}

}  // namespace jesture