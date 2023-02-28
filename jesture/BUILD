load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "config_manager",
    srcs = ["config_manager.cc"],
    moc_hdrs = ["config_manager.h"],
    deps = [
        "@qt//:qt_core",
    ],
)

qt_cc_library(
    name = "main_window",
    srcs = ["main_window.cc"],
    data = [
        "//icons:add_element.svg",
        "//icons:hide.svg",
        "//icons:quit.svg",
        "//icons:settings.svg",
        "//icons:show.svg",
    ],
    moc_hdrs = ["main_window.h"],
    deps = [
        "//jesture/components:frame_view",
        "//jesture/components:gesture_editor",
        "//jesture/jesturepipe:controller",
        "@qt//:qt_core",
        "@qt//:qt_gui",
        "@qt//:qt_multimedia",
        "@qt//:qt_widgets",
    ],
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    data = [
        "//icons:settings.svg",
    ],
    deps = [
        ":config_manager",
        ":main_window",
        "//jesture/jesturepipe:controller",
        "//jesture/jesturepipe:settings",
        "@bazel_tools//tools/cpp/runfiles",
        "@qt//:qt_core",
        "@qt//:qt_widgets",
    ],
)
