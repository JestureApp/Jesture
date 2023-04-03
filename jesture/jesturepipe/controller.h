#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>

#include "jesture/managers/camera.h"
#include "jesture/managers/resources.h"
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

    // ~JesturePipeController() noexcept;

   private slots:
    void processVideoFrame(const QVideoFrame& video_frame);

   private:
    Camera* camera;
    jesturepipe::JesturePipe pipeline;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H