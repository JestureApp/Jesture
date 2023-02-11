load("@rules_cc//cc:defs.bzl", "objc_library")

cc_library(
    name = "glfw_src",
    srcs = [
        "src/context.c",
        "src/egl_context.c",
        "src/init.c",
        "src/input.c",
        "src/osmesa_context.c",
        "src/monitor.c",
        "src/window.c",
        "src/xkb_unicode.c",
    ] + select({
        "@platforms//os:windows": [
            "src/win32_init.c",
            "src/win32_joystick.c",
            "src/win32_monitor.c",
            "src/win32_thread.c",
            "src/win32_time.c",
            "src/win32_window.c",
            "src/wgl_context.c",
        ],
        "@platforms//os:macos": [
            "src/cocoa_time.c",
            "src/posix_thread.c",
        ],
        "@platforms//os:linux": [
            "src/glx_context.c",
            "src/linux_joystick.c",
            "src/posix_thread.c",
            "src/posix_time.c",
            "src/x11_init.c",
            "src/x11_monitor.c",
            "src/x11_window.c",
        ],
    }),
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/egl_context.h",
        "src/internal.h",
        "src/osmesa_context.h",
        "src/mappings.h",
        "src/xkb_unicode.h"
    ] + select({
        "@platforms//os:windows": [
            "src/win32_joystick.h",
            "src/win32_platform.h",
            "src/wgl_context.h", 
        ],
        "//conditions:default": [
            "src/glx_context.h",
            "src/linux_joystick.h",
            "src/posix_thread.h",
            "src/posix_time.h",
            "src/x11_platform.h",
        ],
    }),
    defines = ["GLFW_INVALID_CODEPOINT"] + select({
        "@platforms//os:windows": [
            "_GLFW_WIN32",
        ],
        "//conditions:default": [
            "_GLFW_HAS_XF86VM",
            "_GLFW_X11",
        ],
    }),
    linkopts = select({
        "@platforms//os:windows": [
            "-DEFAULTLIB:user32.lib",
            "-DEFAULTLIB:gdi32.lib",
            "-DEFAULTLIB:shell32.lib",
        ],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:private"],
)

cc_library(
    name = "glfw",
    hdrs = [
        "include/GLFW/glfw3.h"
    ],
    deps = [
        ":glfw_src",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)