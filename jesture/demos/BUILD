load("//qt:qt.bzl", "qt_cc_binary")

package(default_visibility = ["//visibility:public"])

exports_files(["Info.plist"])

qt_cc_binary(
    name = "frame_view_demo",
    srcs = ["frame_view_demo.cc"],
    data = [":Info.plist"],
    deps = [
        "//jesture/components:frame_view",
        "//jesture/jesturepipe:controller",
        "//jesture/jesturepipe:settings",
        "@bazel_tools//tools/cpp/runfiles",
        "@qt//:qt_core",
        "@qt//:qt_widgets",
    ],
)
