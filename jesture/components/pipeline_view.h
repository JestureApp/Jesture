#ifndef JESTURE_COMPONENTS_PIPELINE_VIEW_H
#define JESTURE_COMPONENTS_PIPELINE_VIEW_H

#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsView>
#include <QWidget>

#include "jesture/managers/camera.h"

namespace jesture {

class PipelineView : public QGraphicsView {
    Q_OBJECT
   public:
    explicit PipelineView(Camera* camera, QWidget* parent = nullptr);

   protected:
    void resizeEvent(QResizeEvent* event) override;

   private slots:
    void updateSizes(const QSizeF& video_size);
    void updateReflection();

   private:
    Camera* camera;
    QGraphicsVideoItem* camera_feed;
    QGraphicsScene* scene;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_PIPELINE_VIEW_H