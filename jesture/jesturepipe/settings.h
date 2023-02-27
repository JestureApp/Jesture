#ifndef JESTURE_JESTUREPIPE_SETTINGS_H
#define JESTURE_JESTUREPIPE_SETTINGS_H

#include <string>

namespace jesture {
typedef struct {
    int camera_index;
    int mode;
} JesturePipeSettings;

typedef struct {
    std::string palm_model_full_path;
    std::string palm_model_lite_path;
    std::string landmark_model_full_path;
    std::string landmark_model_lite_path;
} JesturePipeInit;
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_SETTINGS_H