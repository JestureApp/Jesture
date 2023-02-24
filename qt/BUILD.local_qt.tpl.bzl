"""
Local Qt installation helper functions
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

def local_qt_include_path():
    return "${include_path}"

def local_qt_lib_path():
    return "${lib_path}"

def qt_module(name, include_dir, lib, deps = []):
    native.cc_library(
        name = '%s_linux' % name,
        hdrs = native.glob(["%s/**" % include_dir], allow_empty = True),
        includes = ["."],
        linkopts = ["-l%s" % lib],
        target_compatible_with = ["@platforms//os:linux"],
    )
    
    native.cc_library(
        name = '%s_osx' % name,
        hdrs = native.glob(["%s/**" % include_dir], allow_empty = True),
        includes = ["."],
        linkopts = [
            "-F%s" % local_qt_lib_path(),
            "-l%s" % lib.replace("6", ""),
        ],
        target_compatible_with = ["@platforms//os:osx"],
    )

    native.cc_library(
        name = name, 
        visibility = ["//visibility:public"],
        deps = deps + select({
            "@platforms//os:linux": ["%s_linux" % name],
            "@platforms//os:osx": ["%s_osx" % name],
        }),
    )

