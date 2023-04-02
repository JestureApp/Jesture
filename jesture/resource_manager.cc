#include "jesture/resource_manager.h"

#include <iostream>

namespace jesture {
namespace fs = std::filesystem;

ResourceManager::ResourceManager(char *argv0) {
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

QIcon ResourceManager::getIcon(QString path) {
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

bool ResourceManager::supportsImageFormat(std::string format) {
    return QImageReader::supportedImageFormats().contains(format.c_str());
}

QIcon ResourceManager::applicationWindowIcon() {
    if (supportsImageFormat("svg"))
        return getIcon(":/jesture/icons/jesture.svg");

    if (supportsImageFormat("ico"))
        return getIcon(":/jesture/icons/jesture.ico");

    qFatal("Cannot load %s", ":/jesture/icons/jesture.*");
}

void ResourceManager::ensureExists(fs::path path) {
    if (!fs::exists(path)) qFatal("Could not find file %s", path.c_str());
}

}  // namespace jesture