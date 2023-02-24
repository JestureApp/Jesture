"""
Setup for a workspace dependent on JesturePipe
"""

load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@local_config_qt//:local_qt.bzl", "local_qt_base_path")
load("@jesturepipe//:setup0.bzl", "jesturepipe_setup0")

def jesture_setup1():
    """
    Setup for a workspace dependent on JesturePipe
    """

    maybe(
        native.new_local_repository,
        name = "qt",
        build_file = "@jesture//third_party:qt.BUILD",
        path = local_qt_base_path(),
    )

    jesturepipe_setup0()
