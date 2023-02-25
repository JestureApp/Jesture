#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QThread>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "jesture/jesturepipe/worker.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
class JesturePipeController : public QObject {
    Q_OBJECT
   public:
    static absl::StatusOr<JesturePipeController> Create(
        JesturePipeInit init) noexcept;

    JesturePipeController(JesturePipeController &other) = delete;
    JesturePipeController &operator=(JesturePipeWorker &other) = delete;

    JesturePipeController(JesturePipeController &&other) = delete;
    JesturePipeController &operator=(JesturePipeController &&other) = delete;

    ~JesturePipeController() noexcept;

   public slots:
    absl::Status Start(JesturePipeSettings settings) noexcept;
    void Stop() noexcept;
    void forwardFrame(cv::Mat frame) noexcept;

   private:
    JesturePipeController(JesturePipeWorker *worker) noexcept;
    QThread workerThread;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H