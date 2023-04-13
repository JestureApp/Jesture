#ifndef JESTURE_COMPONENTS_LANDMARKS_ITEM_H
#define JESTURE_COMPONENTS_LANDMARKS_ITEM_H

// #include <QGraphicsObject>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QObject>
#include <QPen>
#include <QTimer>

#include "jesture/jesturepipe/landmarks.h"

namespace jesture {

class LandmarksItem : public QObject, public QGraphicsItem {
    Q_OBJECT
   public:
    explicit LandmarksItem(QGraphicsItem *parent);

    // ~LandmarksItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

    QRectF boundingRect() const override;

    QPen pen() const;
    QBrush brush() const;

   public slots:
    void setSize(const QSizeF &size);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    void updateLandmarks(Landmarks landmarks);

   private:
    QSizeF size;
    QPen m_pen;
    QBrush m_brush;
    QTimer *valid_timer;
    std::array<QLineF, NUM_LANDMARK_CONNECTIONS> lines;
    std::array<QPointF, NUM_LANDMARK_POINTS> points;
};

}  // namespace jesture

#endif  // JESTURE_COMPONENTS_LANDMARKS_ITEM_H