""" 
Dependency management 
"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def jesture_repositories():
    """Load dependencies for jesture."""

    maybe(
        http_archive,
        name = "bazel_skylib",
        urls = [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/releases/download/1.3.0/bazel-skylib-1.3.0.tar.gz",
        ],
        sha256 = "74d544d96f4a5bb630d465ca8bbcfe231e3594e5aae57e1edbf17a6eb3ca2506",
    )

    maybe(
        git_repository,
        name = "actions",
        remote = "git@capstone-cs.eng.utah.edu:jesture/actions.git",
        commit = "8ebd373380467080dd2508864ce7d43a4abef58a",
        # shallow_since = "1677290156 -0700",
        # tag = "v0.1.1",
    )

    maybe(
        git_repository,
        name = "jesturepipe",
        remote = "git@capstone-cs.eng.utah.edu:jesture/jesturepipe.git",
        commit = "c00af16c399eabc12331cff992aaa8593c460dc2",
        # shallow_since = "1677290156 -0700",
        # tag = "v0.1.1",
    )

    # maybe(
    #     native.local_repository,
    #     name = "jesturepipe",
    #     path = "../JesturePipe",
    # )
