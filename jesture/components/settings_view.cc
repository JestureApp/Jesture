#include "jesture/components/settings_view.h"

#include <QLabel>

namespace jesture {
SettingsView::SettingsView(QWidget* parent) : QWidget(parent) {
    auto title = new QLabel("Settings", this);
}
}  // namespace jesture
