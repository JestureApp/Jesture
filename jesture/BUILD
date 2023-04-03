load("//qt:qt.bzl", "qt_cc_binary", "qt_cc_library")
load("//jesture/tool:resource_folder.bzl", "resource_folder")

package(default_visibility = ["//visibility:public"])

resource_folder(
    name = "models",
    dir_name = "models",
    file_targets = {
        "hand_landmark_full.tflite": "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_full.tflite",
        "hand_landmark_lite.tflite": "@mediapipe//mediapipe/modules/hand_landmark:hand_landmark_lite.tflite",
        "palm_detection_full.tflite": "@mediapipe//mediapipe/modules/palm_detection:palm_detection_full.tflite",
        "palm_detection_lite.tflite": "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    },
)

qt_cc_library(
    name = "main_window",
    srcs = ["main_window.cc"],
    moc_hdrs = ["main_window.h"],
    deps = [
        "@qt//:qt_widgets",
    ],
)

qt_cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    data = [
        ":models",
    ],
    env = {
        "QT_PLUGIN_PATH": "/usr/lib/x86_64-linux-gnu/qt6/plugins",
    },
    deps = [
        ":main_window",
        "//jesture/jesturepipe:controller",
        "//jesture/managers:resources",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@qt//:qt_multimedia",
        "@qt//:qt_widgets",
    ],
)
