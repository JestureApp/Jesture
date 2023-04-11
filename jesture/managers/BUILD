load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "resources",
    srcs = ["resources.cc"],
    hdrs = ["resources.h"],
    copts = select({
        "//conditions:default": ["-fPIC"],
    }),
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
        "//jesture/jesturepipe:action",
        "//jesture/jesturepipe:gesture",
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
