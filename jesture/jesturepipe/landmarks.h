#ifndef JESTURE_JESTUREPIPE_LANDMARKS_H
#define JESTURE_JESTUREPIPE_LANDMARKS_H

#include <list>

#include "mediapipe/framework/formats/landmark.pb.h"

namespace jesture {

typedef enum LandmarkPoint : int {
    WRIST = 0,
    THUMB_CMC = 1,
    THUMB_MCP = 2,
    THUMB_IP = 3,
    THUMB_TIP = 4,
    INDEX_FINGER_MCP = 5,
    INDEX_FINGER_PIP = 6,
    INDEX_FINGER_DIP = 7,
    INDEX_FINGER_TIP = 8,
    MIDDLE_FINGER_MCP = 9,
    MIDDLE_FINGER_PIP = 10,
    MIDDLE_FINGER_DIP = 11,
    MIDDLE_FINGER_TIP = 12,
    RING_FINGER_MCP = 13,
    RING_FINGER_PIP = 14,
    RING_FINGER_DIP = 15,
    RING_FINGER_TIP = 16,
    PINKY_MCP = 17,
    PINKY_PIP = 18,
    PINKY_DIP = 19,
    PINKY_TIP = 20,
} LandmarkPoint;

constexpr int NUM_LANDMARK_POINTS = 21;

constexpr int NUM_LANDMARK_CONNECTIONS = 21;

const std::array<std::pair<LandmarkPoint, LandmarkPoint>,
                 NUM_LANDMARK_CONNECTIONS>
    LANDMARK_CONNECTIONS{{{WRIST, THUMB_CMC},
                          {WRIST, INDEX_FINGER_MCP},
                          {WRIST, PINKY_MCP},
                          {INDEX_FINGER_MCP, MIDDLE_FINGER_MCP},
                          {MIDDLE_FINGER_MCP, RING_FINGER_MCP},
                          {RING_FINGER_MCP, PINKY_MCP},

                          {THUMB_CMC, THUMB_MCP},
                          {THUMB_MCP, THUMB_IP},
                          {THUMB_IP, THUMB_TIP},

                          {INDEX_FINGER_MCP, INDEX_FINGER_PIP},
                          {INDEX_FINGER_PIP, INDEX_FINGER_DIP},
                          {INDEX_FINGER_DIP, INDEX_FINGER_TIP},

                          {MIDDLE_FINGER_MCP, MIDDLE_FINGER_PIP},
                          {MIDDLE_FINGER_PIP, MIDDLE_FINGER_DIP},
                          {MIDDLE_FINGER_DIP, MIDDLE_FINGER_TIP},

                          {RING_FINGER_MCP, RING_FINGER_PIP},
                          {RING_FINGER_PIP, RING_FINGER_DIP},
                          {RING_FINGER_DIP, RING_FINGER_TIP},

                          {PINKY_MCP, PINKY_PIP},
                          {PINKY_PIP, PINKY_DIP},
                          {PINKY_DIP, PINKY_TIP}}};

using Landmarks = mediapipe::NormalizedLandmarkList;

}  // namespace jesture

#endif  // JESTURE_JESTUREPIPE_LANDMARKS_H