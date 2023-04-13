#include "jesture/components/settings_view.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QMediaDevices>
#include <QSlider>
#include <QString>

namespace jesture {
SettingsView::SettingsView(Config* config, QWidget* parent) : QWidget(parent) {
    auto layout = new QGridLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setAlignment(Qt::AlignTop);

    auto title = new QLabel("Settings", this);

    title->setStyleSheet(
        "font-size: 24px; font-weight: 700; margin-bottom: 12px;");

    layout->addWidget(title, 0, 0, 1, 2);

    auto accuracy_label = new QLabel("Gesture Recognition Accuracy", this);
    auto accuracy_combo = new QComboBox(this);
    auto accuracy_explanation = new QLabel(
        "Setting accuracy to diminished may improve performance on lower-end "
        "hardware.",
        this);

    accuracy_label->setWordWrap(true);
    accuracy_combo->addItem("Full");
    accuracy_combo->addItem("Diminished");
    accuracy_explanation->setWordWrap(true);
    accuracy_explanation->setStyleSheet("color: gray; font-weight: 400;");

    connect(accuracy_combo, &QComboBox::currentIndexChanged, this,
            &SettingsView::combo_index_to_accuracy);
    connect(this, &SettingsView::accuracy_changed, config,
            &Config::setPipelineSettings);

    layout->addWidget(accuracy_label, 1, 0);
    layout->addWidget(accuracy_combo, 1, 1);
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

    connect(camera_combo, &QComboBox::currentIndexChanged, this,
            &SettingsView::combo_index_to_camera_device);
    connect(this, &SettingsView::camera_changed, config,
            &Config::cameraDeviceChanged);

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
    camera_zoom_explanation->setStyleSheet("color: gray; font-weight: 400;");

    layout->addWidget(camera_zoom_label, 4, 0);
    layout->addWidget(camera_zoom_slider, 4, 1);
    layout->addWidget(camera_zoom_explanation, 5, 0, 1, 2);
}

void SettingsView::combo_index_to_camera_device(int index) {
    auto devices = QMediaDevices::videoInputs();
    camera_changed(devices[index]);
}

void SettingsView::combo_index_to_accuracy(int index) {
    accuracy_changed(index == 0);
}
}  // namespace jesture
