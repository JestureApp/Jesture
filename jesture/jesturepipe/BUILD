load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "controller",
    srcs = ["controller.cc"],
    moc_hdrs = ["controller.h"],
    deps = [
        ":action",
        ":gesture",
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

cc_library(
    name = "landmarks",
    hdrs = ["landmarks.h"],
    deps = [
        "@mediapipe//mediapipe/framework/formats:landmark_cc_proto",
    ],
)

cc_library(
    name = "gesture",
    srcs = ["gesture.cc"],
    hdrs = ["gesture.h"],
    deps = [
        "@jesturepipe//jesturepipe/gesture",
    ],
)

qt_cc_library(
    name = "action",
    srcs = ["action.cc"],
    hdrs = ["action.h"],
    deps = [
        "@com_google_absl//absl/status:statusor",
        "@jesturepipe//jesturepipe/actions:action",
        "@qt//:qt_gui",
    ],
)
