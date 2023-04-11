#include "jesture/components/recording_view.h"

#include <QLabel>

namespace jesture {
RecordingView::RecordingView(QWidget* parent) : QWidget(parent) {
    auto title = new QLabel("Recording View", this);
}
}  // namespace jesture
