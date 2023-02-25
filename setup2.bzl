"""
Setup for a workspace dependent on JesturePipe
"""

load("@jesturepipe//:setup1.bzl", "jesturepipe_setup1")

def jesture_setup2():
    """
    Setup for a workspace dependent on JesturePipe
    """

    jesturepipe_setup1()
