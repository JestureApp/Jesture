#ifndef JESTURE_UTIL_VIDEO_CAPTURE_SESSION_H
#define JESTURE_UTIL_VIDEO_CAPTURE_SESSION_H

#include <QMediaCaptureSession>
#include <QVideoSink>

namespace jesture {

class VideoCaptureSession : public QObject {
    Q_OBJECT

   public:
    explicit VideoCaptureSession(QCamera* camera, QObject* parent = nullptr);

    void addVideoSink(QVideoSink* sink);

   private:
    QMediaCaptureSession* capture_session;
    QVideoSink* sink;
};

}  // namespace jesture

#endif  // JESTURE_UTIL_VIDEO_CAPTURE_SESSION_H