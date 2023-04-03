#include "jesture/util/video_capture_session.h"

namespace jesture {

VideoCaptureSession::VideoCaptureSession(QCamera* camera, QObject* parent)
    : QObject(parent) {
    sink = new QVideoSink(this);

    capture_session = new QMediaCaptureSession(this);
    capture_session->setCamera(camera);
    capture_session->setVideoSink(sink);
}

void VideoCaptureSession::addVideoSink(QVideoSink* new_sink) {
    QObject::connect(sink, &QVideoSink::videoFrameChanged, new_sink,
                     &QVideoSink::setVideoFrame);
}

}  // namespace jesture