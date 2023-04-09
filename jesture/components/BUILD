load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "pipeline_view",
    srcs = ["pipeline_view.cc"],
    moc_hdrs = ["pipeline_view.h"],
    deps = [
        ":landmarks_item",
        "//jesture/jesturepipe:landmarks",
        "//jesture/managers:camera",
        "@qt//:qt_multimedia",
        "@qt//:qt_multimedia_widgets",
        "@qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "landmarks_item",
    srcs = ["landmarks_item.cc"],
    moc_hdrs = ["landmarks_item.h"],
    deps = [
        "//jesture/jesturepipe:landmarks",
        "@qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "sidebar",
    srcs = ["sidebar.cc"],
    moc_hdrs = ["sidebar.h"],
    deps = [
        "@qt//:qt_widgets",
    ]
)