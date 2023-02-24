"""
Setup for a workspace dependent on JesturePipe
"""

load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@local_config_qt//:local_qt.bzl", "local_qt_include_path")
load("@jesturepipe//:setup1.bzl", "jesturepipe_setup1")

def jesture_setup2():
    """
    Setup for a workspace dependent on JesturePipe
    """

    jesturepipe_setup1()
