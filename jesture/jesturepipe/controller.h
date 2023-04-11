#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>

#include "jesture/jesturepipe/action.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesture/managers/camera.h"
#include "jesture/managers/resources.h"
#include "jesturepipe/gesture/gesture.h"
#include "jesturepipe/jesturepipe.h"

namespace jesture {

class JesturePipeController : public QObject {
    Q_OBJECT
   public:
    static jesturepipe::JesturePipeConfig makeConfig(
        const Resources& resources);

    explicit JesturePipeController(Camera* camera,
                                   const jesturepipe::JesturePipeConfig& config,
                                   QObject* parent = nullptr);

    ~JesturePipeController();

    bool isRunning() const;

   signals:
    void landmarksReady(
        std::vector<mediapipe::NormalizedLandmarkList> landmarks,
        unsigned long timestamp);
    void gestureRecognized(int gesture_id, unsigned long timestamp);

   public slots:
    void start(bool use_full);
    void stop();

    void setGesture(int gesture_id, Gesture gesture);
    void removeGesture(int gesture_id);
    void clearGestures();

    void setAction(int gesture_id, Action action);
    void removeAction(int gesture_id);

   private slots:
    void processVideoFrame(const QVideoFrame& video_frame);

   private:
    absl::Status onGestureRecognized(int gesture_id, unsigned long timestamp);
    absl::Status onGestureRecorded(jesturepipe::Gesture gesture,
                                   unsigned long timestamp);
    absl::Status onLandmarks(
        std::vector<mediapipe::NormalizedLandmarkList> landmarks,
        unsigned long timestamp);

    Camera* camera;
    jesturepipe::JesturePipe pipeline;
    int frame_time = 0;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H