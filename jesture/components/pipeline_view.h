#ifndef JESTURE_COMPONENTS_PIPELINE_VIEW_H
#define JESTURE_COMPONENTS_PIPELINE_VIEW_H

#include <QBrush>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QPen>
#include <QWidget>

#include "jesture/components/landmarks_item.h"
#include "jesture/jesturepipe/landmarks.h"
#include "jesture/managers/camera.h"

namespace jesture {

class PipelineView : public QGraphicsView {
    Q_OBJECT
   public:
    explicit PipelineView(Camera* camera, QWidget* parent = nullptr);

   public slots:
    void drawLandmarks(std::vector<Landmarks> landmarks);

   protected:
    void resizeEvent(QResizeEvent* event) override;

   private slots:
    void updateSizes(const QSizeF& video_size);
    void updateReflection();

   private:
    Camera* camera;
    LandmarksItem* first_hand_landmarks;
    LandmarksItem* second_hand_landmarks;
    QGraphicsVideoItem* camera_feed;
    QGraphicsScene* scene;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_PIPELINE_VIEW_H