#include "jesture/components/settings_view.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QMediaDevices>
#include <QSlider>
#include <QString>

namespace jesture {
SettingsView::SettingsView(QWidget* parent) : QWidget(parent) {
    auto parent_layout = new QVBoxLayout(this);
    auto layout = new QGridLayout(this);
    parent_layout->addLayout(layout);
    layout->setContentsMargins(20, 20, 20, 20);
    parent_layout->addSpacing(100);

    auto title = new QLabel("Settings", this);
    layout->addWidget(title, 0, 0, 1, 2);

    auto accuracy_label = new QLabel("Gesture Recognition Accuracy", this);
    auto accuracy_slider = new QSlider(Qt::Horizontal, this);
    auto accuracy_explanation = new QLabel(
        "Higher values mean better gesture recognition at a lower performance, "
        "and the opposite is true for lower values.",
        this);

    accuracy_label->setWordWrap(true);
    accuracy_explanation->setWordWrap(true);

    layout->addWidget(accuracy_label, 1, 0);
    layout->addWidget(accuracy_slider, 1, 1);
    layout->addWidget(accuracy_explanation, 2, 0, 1, 2);

    auto camera_label = new QLabel("Camera", this);
    auto camera_combo = new QComboBox(this);

    QList<QString> camera_descriptions;
    for (const auto& camera : QMediaDevices::videoInputs()) {
        camera_descriptions.append(camera.description());
    }
    camera_combo->addItems(camera_descriptions);
    camera_combo->setCurrentText(
        QMediaDevices::defaultVideoInput().description());
    connect(camera_combo, &QComboBox::currentTextChanged, this,
            &SettingsView::camera_changed);

    layout->addWidget(camera_label, 3, 0);
    layout->addWidget(camera_combo, 3, 1);

    auto camera_zoom_label = new QLabel("Camera Zoom", this);
    auto camera_zoom_slider = new QSlider(Qt::Horizontal, this);
    auto camera_zoom_explanation = new QLabel(
        "Zooming the camera in can sometimes help to recognize gestures when "
        "you are far away from the camera, but it's not perfect. We recommend "
        "staying close to the camera while using Jesture.",
        this);

    camera_zoom_label->setWordWrap(true);
    camera_zoom_explanation->setWordWrap(true);

    layout->addWidget(camera_zoom_label, 4, 0);
    layout->addWidget(camera_zoom_slider, 4, 1);
    layout->addWidget(camera_zoom_explanation, 5, 0, 1, 2);
}
}  // namespace jesture
