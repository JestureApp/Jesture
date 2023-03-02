#include "jesture/jesturepipe/controller.h"

#include <QDebug>

#include "absl/status/status.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
using namespace std::placeholders;
const char OutputFrameStream[] = "annotated_frame";
const char AddGestureStream[] = "add_gesture";
const char IsRecordingStream[] = "is_recording";
const char RecognizedGestureStream[] = "recognized_gestures";
const char RecordedGestureStream[] = "recorded_gestures";
}  // namespace

void check_status(absl::Status status) {
    if (!status.ok()) qFatal("%s", status.ToString().c_str());
}

template <typename T>
void add_packet(mediapipe::CalculatorGraph *graph, const std::string &stream,
                T packet, int timestamp) {
    check_status(graph->AddPacketToInputStream(
        stream,
        mediapipe::MakePacket<T>(packet).At(mediapipe::Timestamp(timestamp))));
}

JesturePipeController::JesturePipeController(JesturePipeInit init,
                                             QObject *parent) noexcept
    : QObject(parent), running(false), recording(false), timestamp(0) {
    check_status(jesturepipe::jesturepipe_graph(
        &graph, init.palm_model_full_path, init.palm_model_lite_path,
        init.landmark_model_full_path, init.landmark_model_lite_path));
}

JesturePipeController::~JesturePipeController() noexcept { Stop(); }

void JesturePipeController::Start(JesturePipeSettings settings) noexcept {
    if (running) return;

    const std::map<std::string, mediapipe::Packet> side_packets{
        {"camera_index",
         mediapipe::MakePacket<int>(settings.camera_index).At(mediapipe::Timestamp(0))},
        {"mode", mediapipe::MakePacket<int>(settings.mode).At(mediapipe::Timestamp(0))}};

    check_status(graph.ObserveOutputStream(
        OutputFrameStream,
        std::bind(&JesturePipeController::onFrame, this, _1)));

    check_status(graph.ObserveOutputStream(
        RecognizedGestureStream,
        std::bind(&JesturePipeController::onGestureRecognized, this, _1)));

    check_status(graph.ObserveOutputStream(
        RecordedGestureStream,
        std::bind(&JesturePipeController::onGestureRecorded, this, _1)));

    check_status(graph.StartRun(side_packets));

    running = true;
}

void JesturePipeController::Stop() noexcept {
    if (!running) return;

    check_status(graph.CloseAllPacketSources());

    check_status(graph.WaitUntilDone());

    running = false;
}

void JesturePipeController::updateSettings(
    JesturePipeSettings settings) noexcept {
    Stop();
    Start(settings);
}

void JesturePipeController::addGesture(jesturepipe::Gesture gesture) noexcept {
    // check_status(graph.AddPacketToInputStream(
    //     AddGestureStream,
    //     mediapipe::MakePacket<jesturepipe::Gesture>(gesture).At(
    //         mediapipe::Timestamp().NextAllowedInStream())));

    add_packet(&graph, AddGestureStream, gesture, timestamp++);
}

void JesturePipeController::toggleRecording() noexcept {
    add_packet(&graph, IsRecordingStream, !recording, timestamp++);

    recording = !recording;
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

absl::Status JesturePipeController::onGestureRecognized(
    mediapipe::Packet gesture_packet) noexcept {
    int gesture_id = gesture_packet.Get<int>();

    emit gestureRecognizer(gesture_id);

    return absl::OkStatus();
}

absl::Status JesturePipeController::onGestureRecorded(
    mediapipe::Packet gesture_packet) noexcept {
    jesturepipe::Gesture gesture = gesture_packet.Get<jesturepipe::Gesture>();

    emit gestureRecorded(gesture);

    return absl::OkStatus();
}

}  // namespace jesture