#ifndef JESTURE_RESOURCE_MANAGER_H
#define JESTURE_RESOURCE_MANAGER_H

#include <QtWidgets>
#include <filesystem>

namespace jesture {
namespace fs = std::filesystem;

class ResourceManager {
   public:
    ResourceManager(char *argv0);

    QIcon applicationWindowIcon();

   private:
    QIcon getIcon(QString path);
    bool supportsImageFormat(std::string format);
    void ensureExists(fs::path path);

    fs::path hand_landmark_full_path;
    fs::path hand_landmark_lite_path;
    fs::path palm_detection_full_path;
    fs::path palm_detection_lite_path;
};
}  // namespace jesture

#endif  // JESTURE_RESOURCE_MANAGER_H