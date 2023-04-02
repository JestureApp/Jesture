load("//qt:qt.bzl", "qt_cc_binary", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "main_window",
    srcs = ["main_window.cc"],
    moc_hdrs = ["main_window.h"],
    deps = [
        "@qt//:qt_widgets",
    ],
)

cc_library(
    name = "resource_manager",
    srcs = ["resource_manager.cc"],
    hdrs = ["resource_manager.h"],
    deps = [
        "//icons",
        "@qt//:qt_widgets",
    ],
)

qt_cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    env = {
        "QT_PLUGIN_PATH": "/usr/lib/x86_64-linux-gnu/qt6/plugins",
    },
    deps = [
        ":main_window",
        ":resource_manager",
        "@com_github_google_glog//:glog",
        "@qt//:qt_multimedia",
        "@qt//:qt_widgets",
    ],
)
