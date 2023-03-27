"""
Setup for a workspace dependent on JesturePipe
"""

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
load("@bazel_skylib//lib:versions.bzl", "versions")
load("@jesture//qt:qt_configure.bzl", "qt_configure")
load("@jesturepipe//:repositories.bzl", "jesturepipe_repositories")

def jesture_setup0():
    """
    Setup for a workspace dependent on JesturePipe
    """

    bazel_skylib_workspace()

    versions.check(minimum_bazel_version = "5.0.0", maximum_bazel_version = "5.3.0")

    qt_configure()

    jesturepipe_repositories()
