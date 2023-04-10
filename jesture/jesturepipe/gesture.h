#ifndef JESTURE_JESTUREPIPE_GESTURE_H
#define JESTURE_JESTUREPIPE_GESTURE_H

#include "jesturepipe/gesture/gesture.h"
#include <string>

namespace jesture {
class Gesture {
   public:
    Gesture();
    Gesture(std::string name, jesturepipe::Gesture pipe_gesture);

    std::string name;
    jesturepipe::Gesture pipe_gesture;
};
}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_GESTURE_H