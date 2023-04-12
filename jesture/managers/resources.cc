#include "jesture/managers/resources.h"

#include <QImageReader>
#include <iostream>

namespace jesture {
namespace fs = std::filesystem;

Resources::Resources(char *argv0) {
    fs::path dir = fs::path(argv0).parent_path();

    hand_landmark_full_path = dir / "models" / "hand_landmark_full.tflite";
    ensureExists(hand_landmark_full_path);

    hand_landmark_lite_path = dir / "models" / "hand_landmark_lite.tflite";
    ensureExists(hand_landmark_lite_path);

    palm_detection_full_path = dir / "models" / "palm_detection_full.tflite";
    ensureExists(palm_detection_full_path);

    palm_detection_lite_path = dir / "models" / "palm_detection_lite.tflite";
    ensureExists(palm_detection_lite_path);
}

QIcon Resources::application_icon() const {
    const QString path(":/jesture/icons/jesture");

    if (supportsImageFormat("svg")) return get_icon(path + ".svg");

    if (supportsImageFormat("ico")) return get_icon(path + ".ico");

    qFatal("Failed loading application icon! No known formats matched!");
}

QIcon Resources::settings_icon() const {
    return get_icon_format_agnostic("settings");
}

QIcon Resources::add_element_icon() const {
    return get_icon_format_agnostic("add_element");
}

QIcon Resources::add_icon() const { return get_icon_format_agnostic("add"); }

QIcon Resources::show_icon() const { return get_icon_format_agnostic("show"); }

QIcon Resources::hide_icon() const { return get_icon_format_agnostic("hide"); }

QIcon Resources::cross_icon() const {
    return get_icon_format_agnostic("cross");
}

fs::path Resources::handLandmarkFullPath() const {
    return hand_landmark_full_path;
}

fs::path Resources::handLandmarkLitePath() const {
    return hand_landmark_lite_path;
}

fs::path Resources::palmDetectionFullPath() const {
    return palm_detection_full_path;
}

fs::path Resources::palmDetectionLitePath() const {
    return palm_detection_lite_path;
}

QIcon Resources::get_icon(QString path) const {
    QImageReader reader(path);

    QImage image = reader.read();
    if (image.isNull()) {
        qFatal("Failed to read icon %s: %s", path.toStdString().c_str(),
               reader.errorString().toStdString().c_str());
    }

    QIcon icon(QPixmap::fromImage(image));

    assert(!icon.isNull());

    return icon;
}

QIcon Resources::get_icon_format_agnostic(QString name) const {
    const QString path(":/jesture/icons/" + name);

    if (supportsImageFormat("svg")) return get_icon(path + ".svg");

    if (supportsImageFormat("png")) return get_icon(path + ".png");

    qFatal("Failed loading icon! No known formats matched!");
}

bool Resources::supportsImageFormat(std::string format) const {
    return QImageReader::supportedImageFormats().contains(format.c_str());
}

void Resources::ensureExists(fs::path path) const {
    if (!fs::exists(path)) qFatal("Could not find file %s", path.c_str());
}

}  // namespace jesture