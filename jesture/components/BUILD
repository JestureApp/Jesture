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

qt_cc_library(
    name = "settings_view",
    srcs = ["settings_view.cc"],
    moc_hdrs = ["settings_view.h"],
    deps = [
        "@qt//:qt_widgets",
        "@qt//:qt_multimedia",
    ]
)

qt_cc_library(
    name = "gesture_list_view",
    srcs = ["gesture_list_view.cc"],
    moc_hdrs = ["gesture_list_view.h"],
    deps = [
        "@qt//:qt_widgets",
        "//jesture/jesturepipe:gesture",
        "//jesture/jesturepipe:action",
        "@jesturepipe//jesturepipe/gesture",
        ":gesture_list_item",
        "//jesture/managers:resources"
    ]
)

qt_cc_library(
    name = "recording_review",
    srcs = ["recording_review.cc"],
    moc_hdrs = ["recording_review.h"],
    deps = [
        "@qt//:qt_widgets",
        "//jesture/jesturepipe:gesture",
        "@jesturepipe//jesturepipe/gesture",
        ":gesture_visualization"
    ]
)

qt_cc_library(
    name = "gesture_list_item",
    srcs = ["gesture_list_item.cc"],
    moc_hdrs = ["gesture_list_item.h"],
    deps = [
        "@qt//:qt_widgets",
        "//jesture/jesturepipe:gesture",
        "//jesture/jesturepipe:action"
    ]
)

qt_cc_library(
    name = "gesture_visualization",
    srcs = ["gesture_visualization.cc"],
    moc_hdrs = ["gesture_visualization.h"],
    deps = [
        "@qt//:qt_widgets",
        "@jesturepipe//jesturepipe/gesture",
    ]
)