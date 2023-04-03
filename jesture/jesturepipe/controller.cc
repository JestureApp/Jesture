#include "jesture/jesturepipe/controller.h"

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
    const jesturepipe::JesturePipeConfig& config, QObject* parent)
    : QObject(parent) {
    LOG(INFO) << "Initializing pipeline";
    check_status("Pipeline initialization", pipeline.Initialize(config));
}
}  // namespace jesture