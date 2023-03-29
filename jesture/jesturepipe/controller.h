#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/opencv_core_inc.h"

namespace jesture {
class JesturePipeController : public QObject {
    Q_OBJECT

    // Q_DISABLE_COPY(JesturePipeController)

    // CHECKME: Not sure I need to disable move, but better safe than sorry for
    // now.
    Q_DISABLE_COPY_MOVE(JesturePipeController)
   public:
    explicit JesturePipeController(const JesturePipeInit& init,
                                   QObject* parent = nullptr) noexcept;

    ~JesturePipeController() noexcept;

   public slots:
    void Start(JesturePipeSettings settings) noexcept;
    void updateSettings(JesturePipeSettings settings) noexcept;
    void addGesture(int gesture_id, jesturepipe::Gesture gesture) noexcept;
    void toggleRecording() noexcept;
    void Stop() noexcept;

   signals:
    void frameReady(cv::Mat frame);
    void gestureRecognizer(int gesture_id);
    void gestureRecorded(jesturepipe::Gesture gesture);
    void landmarksReady(std::vector<mediapipe::NormalizedLandmarkList>);

   private:
    absl::Status onFrame(const mediapipe::Packet& packet) noexcept;
    absl::Status onGestureRecognized(const int& gesture_id) noexcept;
    absl::Status onGestureRecorded(
        const jesturepipe::Gesture& gesture) noexcept;
    absl::Status OnLandmarks(
        const std::vector<mediapipe::NormalizedLandmarkList>) noexcept;

    bool running;
    jesturepipe::JesturePipe pipe;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H