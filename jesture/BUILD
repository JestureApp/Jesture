package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "nuklear_demo",
    srcs = ["nuklear_demo.cc"],
    deps = [
        "@glad//:glad",
        "@nuklear//:nuklear"
    ] + select({
        "@platforms//os:macos": ["@glfw_macos//:glfw"],
        "//conditions:default": ["@glfw//:glfw"],
    }),
)