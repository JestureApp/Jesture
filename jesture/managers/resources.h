#ifndef JESTURE_MANAGERS_RESOURCES_H
#define JESTURE_MANAGERS_RESOURCES_H

#include <QIcon>
#include <filesystem>

namespace jesture {
namespace fs = std::filesystem;

class Resources {
   public:
    Resources(char *argv0);

    QIcon application_icon() const;
    QIcon settings_icon() const;
    QIcon add_element_icon() const;
    QIcon add_icon() const;
    QIcon show_icon() const;
    QIcon hide_icon() const;

    fs::path handLandmarkFullPath() const;
    fs::path handLandmarkLitePath() const;
    fs::path palmDetectionFullPath() const;
    fs::path palmDetectionLitePath() const;

   private:
    QIcon get_icon(QString path) const;
    QIcon get_icon_format_agnostic(QString name) const;
    bool supportsImageFormat(std::string format) const;
    void ensureExists(fs::path path) const;

    fs::path hand_landmark_full_path;
    fs::path hand_landmark_lite_path;
    fs::path palm_detection_full_path;
    fs::path palm_detection_lite_path;
};
}  // namespace jesture

#endif  // JESTURE_MANAGERS_RESOURCES_H