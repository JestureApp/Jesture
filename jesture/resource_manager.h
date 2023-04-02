#ifndef JESTURE_RESOURCE_MANAGER_H
#define JESTURE_RESOURCE_MANAGER_H

#include <QtWidgets>

namespace jesture {
class ResourceManager {
   public:
    ResourceManager();

    QIcon getIcon(QString path);

    QIcon applicationWindowIcon();
};
}  // namespace jesture

#endif  // JESTURE_RESOURCE_MANAGER_H