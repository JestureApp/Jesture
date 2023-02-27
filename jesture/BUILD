package(default_visibility = ["//visibility:public"])

load("//qt:qt.bzl", "qt_cc_library")

qt_cc_library(
    name = "config_manager",
    moc_hdrs = ["config_manager.h"],
    srcs = ["config_manager.cc"],
    deps = [
        "@qt//:qt_core"
    ]
)

qt_cc_library(
    name = "main_window",
    moc_hdrs = ["main_window.h"],
    srcs = ["main_window.cc"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
        "@qt//:qt_multimedia",
        "//jesture/jesturepipe:controller",
        "//jesture/components:frame_view"
    ],
    data = [
        "//icons:settings.svg",
        "//icons:show.svg",
        "//icons:hide.svg",
        "//icons:quit.svg",
        "//icons:add_element.svg"
    ]
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        ":main_window",
        ":config_manager",
        "//jesture/jesturepipe:controller",
        "//jesture/jesturepipe:settings",
        "@bazel_tools//tools/cpp/runfiles",
    ],
    data = [
        "//icons:settings.svg"
    ]
)
