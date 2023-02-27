#include "jesture/jesturepipe/controller.h"

#include <QDebug>

#include "absl/status/status.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
using namespace std::placeholders;
const char OutputFrameStream[] = "annotated_frame";
const char GestureStream[] = "gestures";
}  // namespace

JesturePipeController::JesturePipeController(JesturePipeInit init,
                                             QObject *parent) noexcept
    : QObject(parent), running(false) {
    absl::Status status = jesturepipe::jesturepipe_graph(
        &graph, init.palm_model_full_path, init.palm_model_lite_path,
        init.landmark_model_full_path, init.landmark_model_lite_path);

    if (!status.ok()) {
        qFatal("%s", status.ToString().c_str());
    }
}

JesturePipeController::~JesturePipeController() noexcept { Stop(); }

void JesturePipeController::Start(JesturePipeSettings settings) noexcept {
    if (running) return;

    const std::map<std::string, mediapipe::Packet> side_packets{
        {"camera_index",
         mediapipe::MakePacket<int>(0).At(mediapipe::Timestamp(0))},
        {"mode", mediapipe::MakePacket<int>(1).At(mediapipe::Timestamp(0))}};

    absl::Status status = graph.ObserveOutputStream(
        OutputFrameStream,
        std::bind(&JesturePipeController::onFrame, this, _1));

    if (!status.ok()) {
        qFatal("%s", status.ToString().c_str());
    }

    status.Update(graph.StartRun(side_packets));

    if (!status.ok()) {
        qFatal("%s", status.ToString().c_str());
    }

    running = true;
}

void JesturePipeController::Stop() noexcept {
    if (!running) return;

    absl::Status status = graph.CloseAllPacketSources();
    if (!status.ok()) {
        qFatal("%s", status.ToString().c_str());
    }

    status.Update(graph.WaitUntilDone());

    if (!status.ok()) {
        qFatal("%s", status.ToString().c_str());
    }

    running = false;
}

void JesturePipeController::updateSettings(
    JesturePipeSettings settings) noexcept {
    Stop();
    Start(settings);
}

void JesturePipeController::addGesture(jesturepipe::Gesture gesture) noexcept {
    absl::Status status = graph.AddPacketToInputStream(
        GestureStream, mediapipe::MakePacket<jesturepipe::Gesture>(gesture).At(
                           mediapipe::Timestamp().NextAllowedInStream()));

    if (!status.ok()) qFatal("%s", status.ToString().c_str());
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