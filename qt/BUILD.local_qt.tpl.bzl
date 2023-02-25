"""
Local Qt installation helper functions
"""

load("@bazel_skylib//lib:paths.bzl", "paths")
load("@jesture//qt/tools:qt_toolchain.bzl", "qt_toolchain")

# TODO: look into setting up a toolchain for binaries

def local_qt_base_path():
    return "${base_path}"

def local_qt_include_path():
    return "${include_path}"

def local_qt_lib_path():
    return "${lib_path}"

def local_qt_bin_path():
    return "${bin_path}"

def qt_module(name, include_dir, lib = None, deps = []):
    inc_path = paths.join(local_qt_include_path(), include_dir)

    extra_linkopts = select({
        "@platforms//os:linux": ["-l%s" % lib],
        "@platforms//os:osx": [
            "-F%s" % paths.join(local_qt_base_path(), local_qt_lib_path()),
            "-framework %s" % lib.replace("6", ""),
        ],
    }) if lib else []

    hdrs = native.glob(["%s/**/*" % inc_path], allow_empty = True)

    native.cc_library(
        name = name,
        visibility = ["//visibility:public"],
        hdrs = hdrs,
        includes = [
            local_qt_include_path(),
            paths.join(local_qt_include_path(), "QtCore"),
        ],
        # CHECKME: might need to link icu (International Components for Unicode)
        linkopts = [] + extra_linkopts,
        deps = deps,
    )

def register_toolchain():
    qt_toolchain(
        name = "qt_local",
        rcc = paths.join(local_qt_base_path(), local_qt_bin_path(), "rcc"),
        moc = paths.join(local_qt_base_path(), local_qt_bin_path(), "moc"),
        visibility = ["//visibility:private"],
    )

def add_binary(name):
    native.filegroup(
        name = name,
        srcs = [paths.join(local_qt_bin_path(), name)],
        visibility = ["//visibility:public"],
    )
