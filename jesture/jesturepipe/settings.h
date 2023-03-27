#ifndef JESTURE_JESTUREPIPE_SETTINGS_H
#define JESTURE_JESTUREPIPE_SETTINGS_H

#include <string>

#include "jesturepipe/jesturepipe.h"

namespace jesture {
typedef struct {
    int camera_index;
    bool use_full;
} JesturePipeSettings;

using JesturePipeInit = jesturepipe::JesturePipeConfig;

}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_SETTINGS_H