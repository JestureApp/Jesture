#include "jesture/resource_manager.h"

namespace jesture {

ResourceManager::ResourceManager() {}

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

QIcon ResourceManager::applicationWindowIcon() {
    return getIcon(":/jesture.ico");
}

}  // namespace jesture