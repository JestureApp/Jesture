"""
Local Qt installation helper functions
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

def local_qt_base_path():
    return "${base_path}"

def local_qt_include_path():
    return "${include_path}"

def local_qt_lib_path():
    return "${lib_path}"

def local_qt_bin_path():
    return "${bin_path}"

def qt_module(name, include_dir, lib, deps = []):
    inc_path = paths.join(local_qt_include_path(), include_dir)

    native.cc_library(
        name = name,
        visibility = ["//visibility:public"],
        hdrs = native.glob(["%s/**/*" % inc_path], allow_empty = True),
        includes = [
            local_qt_include_path(),
            paths.join(local_qt_include_path(), "QtCore"),
        ],
        linkopts = select({
            "@platforms//os:linux": ["-L%s" % lib],
            "@platforms//os:osx": [
                "-F%s" % paths.join(local_qt_base_path(), local_qt_lib_path()),
                "-framework %s" % lib.replace("6", ""),
            ],
        }),
        deps = deps,
    )

def add_binary(name):
    native.filegroup(
        name = name,
        srcs = [paths.join(local_qt_bin_path(), name)],
        visibility = ["//visibility:public"],
    )
