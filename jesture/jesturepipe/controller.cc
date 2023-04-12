#include "jesture/jesturepipe/controller.h"

#include <QVideoFrame>
#include <QVideoSink>

#include "absl/status/status.h"
#include "glog/logging.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_core_inc.h"

namespace jesture {

void check_status(const char* op, absl::Status status) {
    if (!status.ok()) qFatal("%s failed: %s", op, status.ToString().c_str());
}

jesturepipe::JesturePipeConfig JesturePipeController::makeConfig(
    const Resources& resources) {
    return {
        .palm_model_full_path = resources.palmDetectionFullPath(),
        .palm_model_lite_path = resources.palmDetectionLitePath(),
        .hand_landmark_model_full_path = resources.handLandmarkFullPath(),
        .hand_landmark_model_lite_path = resources.handLandmarkLitePath(),
    };
}

JesturePipeController::JesturePipeController(
    Camera* camera, const jesturepipe::JesturePipeConfig& config,
    QObject* parent)
    : QObject(parent), camera(camera) {
    using namespace std::placeholders;

    auto video_sink = new QVideoSink(this);

    QObject::connect(video_sink, &QVideoSink::videoFrameChanged, this,
                     &JesturePipeController::processVideoFrame);

    camera->captureSession()->addVideoSink(video_sink);

    LOG(INFO) << "Initializing pipeline";
    check_status("Pipeline initialization", pipeline.Initialize(config));

    check_status("Landmark Callback",
                 pipeline.OnLandmarks(std::bind(
                     &JesturePipeController::onLandmarks, this, _1, _2)));

    check_status(
        "Gesture Recognition Callback",
        pipeline.OnGestureRecognition(std::bind(
            &JesturePipeController::onGestureRecognized, this, _1, _2)));

    check_status("Gesture Recorded Callback",
                 pipeline.OnRecordedGesture(std::bind(
                     &JesturePipeController::onGestureRecorded, this, _1, _2)));
}

JesturePipeController::~JesturePipeController() { stop(); }

bool JesturePipeController::isRunning() const { return pipeline.isRunning(); }

bool JesturePipeController::isRecording() const {
    return pipeline.IsRecording();
}

void JesturePipeController::restart(bool use_full) {
    stop();
    start(use_full);
}

void JesturePipeController::start(bool use_full) {
    LOG(INFO) << "Starting pipeline";
    check_status("Pipeline start", pipeline.Start(use_full));
}

void JesturePipeController::stop() {
    LOG(INFO) << "Stopping pipeline";
    check_status("Pipeline stop", pipeline.Stop());
}

void JesturePipeController::setRecording(bool recording) {
    LOG(INFO) << "Set recording to " << recording;
    check_status("Pipeline set recording", pipeline.SetRecording(recording));
}

void JesturePipeController::setGesture(int gesture_id, Gesture gesture) {
    pipeline.SetGesture(gesture_id, gesture.pipe_gesture);

    LOG(INFO) << "Added gesture \"" << gesture.name << "\" with id "
              << gesture_id;
}

void JesturePipeController::removeGesture(int gesture_id) {
    pipeline.RemoveGesture(gesture_id);

    LOG(INFO) << "Removed gesture with id " << gesture_id;
}

void JesturePipeController::clearGestures() {
    pipeline.ClearGestures();

    LOG(INFO) << "Cleared gestures";
}

void JesturePipeController::setAction(int gesture_id, ActionsList actions) {
    std::vector<jesturepipe::Action> pipeline_actions;

    for (auto action : actions.action_list) {
        pipeline_actions.push_back(action.pipeline_action);
    }

    jesturepipe::ActionList pipeline_action_list{
        .actions = pipeline_actions, .cursor_control = actions.cursor_control};

    pipeline.SetAction(gesture_id, pipeline_action_list);

    LOG(INFO) << "Added action with id " << gesture_id;
}

void JesturePipeController::removeAction(int gesture_id) {
    pipeline.RemoveAction(gesture_id);

    LOG(INFO) << "Removed gesture with id " << gesture_id;
}

void JesturePipeController::processVideoFrame(const QVideoFrame& video_frame) {
    if (!isRunning()) return;

    // WARNING: const dropped here
    QVideoFrame frame = video_frame;

    if (!frame.isValid()) {
        LOG(WARNING) << "invalid frame";
        return;
    }

    // If frame cannot be mapped, skip
    if (!frame.map(QVideoFrame::ReadOnly)) return;

    QImage img = frame.toImage().convertedTo(QImage::Format_RGB888);

    assert(!img.isNull());

    // https://github.com/dbzhang800/QtOpenCV/blob/master/cvmatandqimage.cpp

    cv::Mat mat(img.height(), img.width(), CV_8UC(img.depth() / 8),
                (uchar*)img.bits(), img.bytesPerLine());

    if (camera->shouldReflect()) {
        // qDebug() << "flipping frame";

        cv::flip(mat, mat, 1);
    }

    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
        mediapipe::ImageFormat::SRGB, mat.cols, mat.rows,
        mediapipe::ImageFrame::kDefaultAlignmentBoundary);

    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());

    mat.copyTo(input_frame_mat);

    unsigned long timestamp = frame_time++;

    check_status("Add frame to pipeline",
                 pipeline.AddFrame(std::move(input_frame), timestamp));

    frame.unmap();
}

absl::Status JesturePipeController::onGestureRecognized(
    int gesture_id, unsigned long timestamp) {
    LOG(INFO) << "Recognized gesture with id " << gesture_id << " at "
              << timestamp;

    emit gestureRecognized(gesture_id, timestamp);

    return absl::OkStatus();
}

absl::Status JesturePipeController::onGestureRecorded(
    jesturepipe::Gesture gesture, unsigned long timestamp) {
    emit gestureRecorded(gesture, timestamp);
    return absl::OkStatus();
}

absl::Status JesturePipeController::onLandmarks(
    std::vector<mediapipe::NormalizedLandmarkList> landmarks,
    unsigned long timestamp) {
    emit landmarksReady(landmarks, timestamp);

    return absl::OkStatus();
}

}  // namespace jesture