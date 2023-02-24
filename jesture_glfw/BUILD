package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    deps = [
        "@glad//:glad",
        "@nuklear//:nuklear",
        "@json//:json",
        "@platform_folders//:platform_folders",
    ] + select({
        "@platforms//os:macos": ["@glfw_macos//:glfw"],
        "//conditions:default": ["@glfw//:glfw"],
    }),
    data = [
        "//third_party:Roboto-Regular.ttf"
    ]
)