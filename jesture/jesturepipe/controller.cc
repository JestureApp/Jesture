#include "jesture/jesturepipe/controller.h"

#include <QVideoSink>

#include "absl/status/status.h"
#include "glog/logging.h"

namespace jesture {

void check_status(const char* op, absl::Status status) {
    if (!status.ok()) qFatal("%s failed: %s", op, status.ToString().c_str());
}

jesturepipe::JesturePipeConfig JesturePipeController::makeConfig(
    const Resources& resources) {
    return {.hand_landmark_model_full_path = resources.handLandmarkFullPath()};
}

JesturePipeController::JesturePipeController(
    Camera* camera, const jesturepipe::JesturePipeConfig& config,
    QObject* parent)
    : QObject(parent), camera(camera) {
    auto video_sink = new QVideoSink(this);

    QObject::connect(video_sink, &QVideoSink::videoFrameChanged, this,
                     &JesturePipeController::processVideoFrame);

    camera->captureSession()->addVideoSink(video_sink);

    LOG(INFO) << "Initializing pipeline";
    check_status("Pipeline initialization", pipeline.Initialize(config));
}

void JesturePipeController::processVideoFrame(const QVideoFrame& video_frame) {
    // TODO
}

}  // namespace jesture