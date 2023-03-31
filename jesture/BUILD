load("//qt:qt.bzl", "qt_cc_binary", "qt_cc_library", "qt_resource")

package(default_visibility = ["//visibility:public"])

exports_files([
    "main.qml",
])

qt_resource(
    name = "jesture_qml",
    files = {
        "main.qml": ":main.qml",
    },
    prefix = "/jesture",
)

qt_cc_library(
    name = "main_window",
    srcs = ["main_window.cc"],
    moc_hdrs = ["main_window.h"],
    deps = [
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
        "//icons",
        "@com_github_google_glog//:glog",
        "@qt//:qt_multimedia",
        "@qt//:qt_qml",
        "@qt//:qt_qml_workerscript",
        "@qt//:qt_quick",
        "@qt//:qt_widgets",
    ],
)
