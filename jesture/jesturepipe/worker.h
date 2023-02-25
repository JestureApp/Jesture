#ifndef JESTURE_JESTUREPIPE_WORKER_H
#define JESTURE_JESTUREPIPE_WORKER_H

#include <QtCore/QObject>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
class JesturePipeWorker : public QObject {
    Q_OBJECT

   public:
    static absl::StatusOr<JesturePipeWorker> Create(
        JesturePipeInit init) noexcept;

    JesturePipeWorker() noexcept;

    JesturePipeWorker(JesturePipeWorker &other) = delete;
    JesturePipeWorker &operator=(JesturePipeWorker &other) = delete;

    JesturePipeWorker(JesturePipeWorker &&other) noexcept;
    JesturePipeWorker &operator=(JesturePipeWorker &&other) noexcept;

   public slots:
    absl::Status Start(JesturePipeSettings settings) noexcept;
    void Stop() noexcept;

   signals:
    void frameReady(cv::Mat frame);

   private:
    std::unique_ptr<mediapipe::CalculatorGraph> graph;
    std::atomic_bool abort_requested;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_WORKER_H