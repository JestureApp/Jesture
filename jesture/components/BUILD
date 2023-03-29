load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "camera_feed",
    srcs = ["camera_feed.cc"],
    moc_hdrs = ["camera_feed.h"],
    deps = [
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
        "@qt//:qt_gui",
        "@qt//:qt_widgets",
        "@qt//:qt_multimedia",
        "@qt//:qt_multimedia_widgets"
    ],
)