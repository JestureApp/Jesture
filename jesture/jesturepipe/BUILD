load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "controller",
    srcs = ["controller.cc"],
    moc_hdrs = ["controller.h"],
    deps = [
        "//jesture/managers:camera",
        "//jesture/managers:resources",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/status",
        "@jesturepipe//jesturepipe",
        "@jesturepipe//jesturepipe/gesture",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
    ],
)
