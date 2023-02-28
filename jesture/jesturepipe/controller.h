#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
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
    explicit JesturePipeController(JesturePipeInit init,
                                   QObject *parent = nullptr) noexcept;

    ~JesturePipeController() noexcept;

   public slots:
    void Start(JesturePipeSettings settings) noexcept;
    void updateSettings(JesturePipeSettings settings) noexcept;
    void addGesture(jesturepipe::Gesture gesture) noexcept;
    void toggleRecording() noexcept;
    void Stop() noexcept;

   signals:
    void frameReady(cv::Mat frame);
    void gestureRecognizer(int gesture_id);
    void gestureRecorded(jesturepipe::Gesture gesture);

   private:
    absl::Status onFrame(mediapipe::Packet frame_packet) noexcept;
    absl::Status onGestureRecognized(mediapipe::Packet gesture_packet) noexcept;
    absl::Status onGestureRecorded(mediapipe::Packet gesture_packet) noexcept;

    bool running;
    bool recording;
    int timestamp;
    mediapipe::CalculatorGraph graph;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H