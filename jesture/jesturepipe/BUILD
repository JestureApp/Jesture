load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "controller",
    srcs = ["controller.cc"],
    moc_hdrs = ["controller.h"],
    deps = [
        ":settings",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@jesturepipe//jesturepipe",
        "@jesturepipe//jesturepipe/gesture",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_core",
        "@qt//:qt_core",
    ],
)

cc_library(
    name = "settings",
    hdrs = ["settings.h"],
    deps = [
        "@jesturepipe//jesturepipe",
    ],
)
