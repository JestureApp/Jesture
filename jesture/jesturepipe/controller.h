#ifndef JESTURE_JESTUREPIPE_CONTROLLER_H
#define JESTURE_JESTUREPIPE_CONTROLLER_H

#include <QObject>

#include "jesture/resource_manager.h"
#include "jesturepipe/jesturepipe.h"

namespace jesture {

class JesturePipeController : public QObject {
    Q_OBJECT
   public:
    static jesturepipe::JesturePipeConfig makeConfig(
        const ResourceManager& resourceManager);

    explicit JesturePipeController(const jesturepipe::JesturePipeConfig& config,
                                   QObject* parent = nullptr);

    // ~JesturePipeController() noexcept;

   private:
    jesturepipe::JesturePipe pipeline;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_CONTROLLER_H