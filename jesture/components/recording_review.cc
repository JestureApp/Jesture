#include "jesture/components/recording_review.h"

#include <QLabel>

namespace jesture {
RecordingReview::RecordingReview(QWidget* parent) : QWidget(parent) {
    auto title = new QLabel("Recording Review", this);
}
}  // namespace jesture
