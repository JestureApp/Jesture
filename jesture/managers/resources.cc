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

QIcon Resources::applicationWindowIcon() const {
    if (supportsImageFormat("svg"))
        return getIcon(":/jesture/icons/jesture.svg");

    if (supportsImageFormat("ico"))
        return getIcon(":/jesture/icons/jesture.ico");

    qFatal("Cannot load %s", ":/jesture/icons/jesture.*");
}

QIcon Resources::settingsIcon() const {
    if (supportsImageFormat("svg"))
        return getIcon(":/jesture/icons/settings.svg");

    if (supportsImageFormat("png"))
        return getIcon(":/jesture/icons/settings.png");

    qFatal("Cannot load %s", ":/jesture/icons/settings.*");
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

QIcon Resources::getIcon(QString path) const {
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

bool Resources::supportsImageFormat(std::string format) const {
    return QImageReader::supportedImageFormats().contains(format.c_str());
}

void Resources::ensureExists(fs::path path) const {
    if (!fs::exists(path)) qFatal("Could not find file %s", path.c_str());
}

}  // namespace jesture