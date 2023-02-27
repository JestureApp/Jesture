#include "jesture/jesturepipe/controller.h"

#include <QDebug>

#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
using namespace std::placeholders;
const char OutputFrameStream[] = "annotated_frame";
}  // namespace

JesturePipeController::JesturePipeController(JesturePipeInit init,
                                             QObject *parent) noexcept
    : QObject(parent), running(false) {
    Q_ASSERT(jesturepipe::jesturepipe_graph(
                 &graph, init.palm_model_full_path, init.palm_model_lite_path,
                 init.landmark_model_full_path, init.landmark_model_lite_path)
                 .ok());
}

JesturePipeController::~JesturePipeController() noexcept { Stop(); }

void JesturePipeController::Start(JesturePipeSettings settings) noexcept {
    if (running) return;

    const std::map<std::string, mediapipe::Packet> side_packets{
        {"camera_index",
         mediapipe::MakePacket<int>(0).At(mediapipe::Timestamp(0))},
        {"mode", mediapipe::MakePacket<int>(1).At(mediapipe::Timestamp(0))},
        {"num_hands",
         mediapipe::MakePacket<int>(2).At(mediapipe::Timestamp(0))}};

    Q_ASSERT(graph
                 .ObserveOutputStream(
                     OutputFrameStream,
                     std::bind(&JesturePipeController::onFrame, this, _1))
                 .ok());

    Q_ASSERT(graph.StartRun(side_packets).ok());

    running = true;
}

void JesturePipeController::Stop() noexcept {
    if (!running) return;

    Q_ASSERT(graph.CloseAllPacketSources().ok());

    Q_ASSERT(graph.WaitUntilDone().ok());

    running = false;
}

void JesturePipeController::updateSettings(
    JesturePipeSettings settings) noexcept {
    Stop();
    Start(settings);
}

absl::Status JesturePipeController::onFrame(
    mediapipe::Packet frame_packet) noexcept {
    // CHECKME: Image manipulation is expensive. Maybe there is a way to check
    // if anyone is listening to the `frameReady` slot.

    // qDebug() << "Got new frame from JesturePipe at "
    //          << frame_packet.Timestamp().Value();

    auto &output_frame = frame_packet.Get<mediapipe::ImageFrame>();

    cv::Mat mat = mediapipe::formats::MatView(&output_frame);

    emit frameReady(mat);

    return absl::OkStatus();
}

}  // namespace jesture