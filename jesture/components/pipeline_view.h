#ifndef JESTURE_COMPONENTS_PIPELINE_VIEW_H
#define JESTURE_COMPONENTS_PIPELINE_VIEW_H

#include <QBrush>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QLabel>
#include <QPen>
#include <QPushButton>
#include <QWidget>

#include "jesture/components/landmarks_item.h"
#include "jesture/jesturepipe/landmarks.h"
#include "jesture/managers/camera.h"

namespace jesture {

class PipelineView : public QGraphicsView {
    Q_OBJECT
   public:
    explicit PipelineView(Camera* camera, QWidget* parent = nullptr);

    QSize sizeHint() const override;

   signals:
    void recording_countdown_finished();

   public slots:
    void drawLandmarks(std::vector<Landmarks> landmarks);
    void show_recording();
    void hide_recording();

   protected:
    void resizeEvent(QResizeEvent* event) override;

   private slots:
    void updateSizes(const QSizeF& video_size);
    void updateReflection();
    void countdown_recording();

   private:
    Camera* camera;
    LandmarksItem* first_hand_landmarks;
    LandmarksItem* second_hand_landmarks;
    QGraphicsVideoItem* camera_feed;
    QGraphicsScene* scene;
    int seconds_to_recording;
    QLabel* hint;
    QPushButton* stop_recording_button;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_PIPELINE_VIEW_H