load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "frame_view",
    srcs = ["frame_view.cc"],
    moc_hdrs = ["frame_view.h"],
    deps = [
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@qt//:qt_gui",
        "@qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "gesture_editor",
    srcs = ["gesture_editor.cc"],
    moc_hdrs = ["gesture_editor.h"],
    deps = [
        ":frame_view",
        "//jesture/jesturepipe:controller",
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@qt//:qt_gui",
        "@qt//:qt_widgets",
    ],
)
