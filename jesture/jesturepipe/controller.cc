#include "jesture/jesturepipe/controller.h"

#include <QDebug>

#include "absl/status/status.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
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

JesturePipeController::JesturePipeController(const JesturePipeInit &init,
                                             QObject *parent) noexcept
    : QObject(parent), running(false) {
    using namespace std::placeholders;

    check_status(pipe.Initialize(init));

    check_status(pipe.OnAnnotatedFrame(
        std::bind(&JesturePipeController::onFrame, this, _1)));
    check_status(pipe.OnGestureRecognition(
        std::bind(&JesturePipeController::onGestureRecognized, this, _1)));
    check_status(pipe.OnRecordedGesture(
        std::bind(&JesturePipeController::onGestureRecorded, this, _1)));

    check_status(pipe.OnLandmarks(
        std::bind(&JesturePipeController::OnLandmarks, this, _1)));
}

JesturePipeController::~JesturePipeController() noexcept { Stop(); }

void JesturePipeController::Start(JesturePipeSettings settings) noexcept {
    if (running) return;

    check_status(pipe.Start(settings.camera_index, settings.use_full));

    running = true;
}

void JesturePipeController::Stop() noexcept {
    if (!running) return;

    check_status(pipe.Stop());

    running = false;
}

void JesturePipeController::updateSettings(
    JesturePipeSettings settings) noexcept {
    Stop();
    Start(settings);
}

void JesturePipeController::addGesture(int gesture_id,
                                       jesturepipe::Gesture gesture) noexcept {
    pipe.AddGesture(gesture_id, std::move(gesture));
}

void JesturePipeController::toggleRecording() noexcept {
    check_status(pipe.SetRecording(!pipe.IsRecording()));
}

absl::Status JesturePipeController::onFrame(
    const mediapipe::Packet &packet) noexcept {
    const mediapipe::ImageFrame &frame = packet.Get<mediapipe::ImageFrame>();

    cv::Mat mat_view = mediapipe::formats::MatView(&frame);

    cv::Mat mat = mat_view.clone();

    emit frameReady(mat);

    return absl::OkStatus();
}

absl::Status JesturePipeController::onGestureRecognized(
    const int &gesture_id) noexcept {
    emit gestureRecognizer(gesture_id);

    return absl::OkStatus();
}

absl::Status JesturePipeController::onGestureRecorded(
    const jesturepipe::Gesture &gesture) noexcept {
    emit gestureRecorded(gesture);

    return absl::OkStatus();
}

absl::Status JesturePipeController::OnLandmarks(
    const std::vector<mediapipe::NormalizedLandmarkList> landmarks) noexcept {
    emit landmarksReady(landmarks);

    return absl::OkStatus();
}

}  // namespace jesture