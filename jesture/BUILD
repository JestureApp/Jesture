package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_world",
    srcs = ["hello_world.cc"]
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
        "@qt//:qt_multimedia",
        "@qt//:qt_multimedia_widgets"
    ]
)