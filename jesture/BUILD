package(
    default_visibility = ["//visibility:public"],
)


genrule(
    name = "copy",
    srcs = ["//third_party/Roboto/Roboto-Regular.ttf"],
    outs = ["regular.ttf"],
    output_to_bindir = 1,
    cmd = "cp $< $@",
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    deps = [
        "@glad//:glad",
        "@nuklear//:nuklear"
    ] + select({
        "@platforms//os:macos": ["@glfw_macos//:glfw"],
        "//conditions:default": ["@glfw//:glfw"],
    }),
)