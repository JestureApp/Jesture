#ifndef JESTURE_MANAGERS_RESOURCES_H
#define JESTURE_MANAGERS_RESOURCES_H

#include <QIcon>
#include <filesystem>

namespace jesture {
namespace fs = std::filesystem;

class Resources {
   public:
    Resources(char *argv0);

    QIcon applicationWindowIcon() const;
    QIcon settingsIcon() const;

    fs::path handLandmarkFullPath() const;
    fs::path handLandmarkLitePath() const;
    fs::path palmDetectionFullPath() const;
    fs::path palmDetectionLitePath() const;

   private:
    QIcon getIcon(QString path) const;
    bool supportsImageFormat(std::string format) const;
    void ensureExists(fs::path path) const;

    fs::path hand_landmark_full_path;
    fs::path hand_landmark_lite_path;
    fs::path palm_detection_full_path;
    fs::path palm_detection_lite_path;
};
}  // namespace jesture

#endif  // JESTURE_MANAGERS_RESOURCES_H