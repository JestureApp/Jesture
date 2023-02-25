#include "jesture/jesturepipe/controller.h"

namespace jesture {

JesturePipeController::JesturePipeController(
    JesturePipeWorker* worker) noexcept {
    worker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);

    // TODO: connections

    workerThread.start();
}

JesturePipeController::~JesturePipeController() noexcept {
    workerThread.quit();
    workerThread.wait();
}

}  // namespace jesture