#ifndef JESTURE_COMPONENTS_RECORDING_REVIEW_H
#define JESTURE_COMPONENTS_RECORDING_REVIEW_H

#include <QString>
#include <QWidget>

#include "jesture/components/gesture_visualization.h"
#include "jesture/jesturepipe/gesture.h"
#include "jesturepipe/gesture/gesture.h"

namespace jesture {

class RecordingReview : public QWidget {
    Q_OBJECT
   public:
    explicit RecordingReview(QWidget* parent = nullptr);

   signals:
    void save_gesture(Gesture gesture);
    void cancel();

   public slots:
    void set_gesture(jesturepipe::Gesture gesture);

   private slots:
    void save();
    void name_change(const QString& text);

   private:
    jesturepipe::Gesture current_gesture;
    GestureVisualization* visualization;
    std::string name;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_RECORDING_REVIEW_H