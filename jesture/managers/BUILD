load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "resources",
    srcs = ["resources.cc"],
    hdrs = ["resources.h"],
    deps = [
        "//icons",
        "@qt//:qt_gui",
        "@qt//:qt_multimedia",
    ],
)

qt_cc_library(
    name = "config",
    srcs = ["config.cc"],
    moc_hdrs = ["config.h"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
    ],
)

qt_cc_library(
    name = "camera",
    srcs = ["camera.cc"],
    moc_hdrs = ["camera.h"],
    deps = [
        "//icons",
        "//jesture/util:video_capture_session",
        "@qt//:qt_multimedia",
    ],
)
