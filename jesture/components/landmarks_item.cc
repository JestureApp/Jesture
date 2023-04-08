#include "jesture/components/landmarks_item.h"

#include <QPainter>

namespace jesture {

LandmarksItem::LandmarksItem(QGraphicsItem *parent)
    : QGraphicsItem(parent), size(1, 1) {
    setVisible(false);

    valid_timer = new QTimer(this);
    valid_timer->setSingleShot(true);

    QObject::connect(valid_timer, &QTimer::timeout, this,
                     [this]() { this->setVisible(false); });
}

void LandmarksItem::setSize(const QSizeF &size) { this->size = size; }

void LandmarksItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
    int point_radius = m_pen.width() / 2;

    painter->setPen(m_pen);
    painter->setBrush(m_brush);

    for (auto &line : lines) {
        painter->drawLine(line.x1() * size.width(), line.y1() * size.height(),
                          line.x2() * size.width(), line.y2() * size.height());
    }

    for (auto &point : points) {
        painter->drawEllipse(point.x() * size.width() - point_radius,
                             point.y() * size.height() - point_radius,
                             2 * point_radius, 2 * point_radius);
    }
}

QRectF LandmarksItem::boundingRect() const { return QRectF(pos(), size); }

QPen LandmarksItem::pen() const { return m_pen; }

void LandmarksItem::setPen(const QPen &pen) {
    m_pen = pen;
    update();
}

QBrush LandmarksItem::brush() const { return m_brush; }

void LandmarksItem::setBrush(const QBrush &brush) {
    m_brush = brush;
    update();
}

void LandmarksItem::updateLandmarks(Landmarks landmarks) {
    setVisible(true);
    valid_timer->start(100);
    auto landmark_points = landmarks.landmark();

    for (int i = 0; i < NUM_LANDMARK_POINTS; i++) {
        points[i].setX(1 - landmark_points[i].x());
        points[i].setY(landmark_points[i].y());
    }

    for (int i = 0; i < NUM_LANDMARK_CONNECTIONS; i++) {
        auto connection = LANDMARK_CONNECTIONS[i];
        auto src_point = landmark_points[connection.first];
        auto dest_point = landmark_points[connection.second];

        lines[i].setLine(1 - src_point.x(), src_point.y(), 1 - dest_point.x(),
                         dest_point.y());
    }

    update();
}

}  // namespace jesture