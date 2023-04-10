#include "jesture/jesturepipe/gesture.h"

namespace jesture {

Gesture::Gesture() {}

Gesture::Gesture(std::string name, jesturepipe::Gesture pipe_gesture)
    : name(name), pipe_gesture(pipe_gesture) {}
}  // namespace jesture