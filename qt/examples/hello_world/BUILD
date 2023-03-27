load("//qt:qt.bzl", "qt_cc_binary")

package(default_visibility = ["//visibility:public"])

exports_files([
    "hello_world.qml",
])

qt_cc_binary(
    name = "hello_world",
    srcs = ["hello_world.cc"],
    data = [
        ":hello_world.qml",
    ],
    deps = [
        "@bazel_tools//tools/cpp/runfiles",
        "@qt//:qt_quick",
    ],
)
