load("//qt:qt.bzl", "qt_cc_library")

package(default_visibility = ["//visibility:public"])

qt_cc_library(
    name = "pipeline_view",
    srcs = ["pipeline_view.cc"],
    moc_hdrs = ["pipeline_view.h"],
    deps = [
        "//jesture/managers:camera",
        "@qt//:qt_multimedia",
        "@qt//:qt_multimedia_widgets",
        "@qt//:qt_widgets",
    ],
)

# qt_cc_library(
#     name = "camera_feed",
#     srcs = ["camera_feed.cc"],
#     moc_hdrs = ["camera_feed.h"],
#     deps = [
#         "//jesture/managers:camera",
#         "@qt//:qt_multimedia",
#         "@qt//:qt_multimedia_widgets",
#         "@qt//:qt_widgets",
#     ],
# )
