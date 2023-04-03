load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "controller",
    srcs = ["controller.cc"],
    moc_hdrs = ["controller.h"],
    deps = [
        "//jesture/managers:camera",
        "//jesture/managers:resources",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/status",
        "@jesturepipe//jesturepipe",
        "@qt//:qt_core",
        "@qt//:qt_multimedia",
    ],
)
