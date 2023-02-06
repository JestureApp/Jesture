package(
    default_visibility = ["//visibility:public"],
)

load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

cmake(
    name = "glfw",
    lib_source = "@glfw//:all_srcs",
    out_static_libs = ["libglfw.a"],
)

cc_binary(
    name = "nuklear_demo",
    srcs = ["nuklear_demo.cc"],
    deps = [
        ":glfw",
    ],
)

cc_binary(
    name = "jesture",
    srcs = ["jesture.cc"],
    deps = [
        ":glfw",
    ],
)