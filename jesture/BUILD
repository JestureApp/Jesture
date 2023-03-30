load("//qt:qt.bzl", "qt_resource")

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

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    env = {
        "QT_PLUGIN_PATH": "/usr/lib/x86_64-linux-gnu/qt6/plugins",
    },
    deps = [
        ":jesture_qml",
        "//icons",
        "@qt//:qt_gui",
        "@qt//:qt_qml",
        "@qt//:qt_qml_workerscript",
        "@qt//:qt_quick",
        "@qt//:qt_widgets",
    ],
)
