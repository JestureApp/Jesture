#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>
// #include <QtGui/QImage>
#include <QImage>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "jesture/jesturepipe/settings.h"
#include "jesturepipe/graphs/jesturepipe/jesturepipe.h"
#include "mediapipe/framework/calculator_framework.h"

namespace jesture {
class JesturePipeController : public QObject {
    Q_OBJECT

    // Q_DISABLE_COPY(JesturePipeController)

    // CHECKME: Not sure I need to disable move, but better safe than sorry for
    // now.
    Q_DISABLE_COPY_MOVE(JesturePipeController)
   public:
    static absl::StatusOr<JesturePipeController *> Create(
        JesturePipeInit init, QObject *parent = nullptr) noexcept;

    explicit JesturePipeController(QObject *parent = nullptr) noexcept;

    ~JesturePipeController() noexcept;

   public slots:
    absl::Status Start(JesturePipeSettings settings) noexcept;
    absl::Status Stop() noexcept;

   signals:
    void frameReady(QImage frame);

   private:
    absl::Status onFrame(mediapipe::Packet frame_packet) noexcept;

    bool running;
    mediapipe::CalculatorGraph graph;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H