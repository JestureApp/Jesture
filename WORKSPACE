workspace(name = "jestureui")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

http_archive(
   name = "rules_foreign_cc",
   sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
   strip_prefix = "rules_foreign_cc-0.9.0",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.9.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://github.com/bazelbuild/rules_foreign_cc/tree/main/docs#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()

_ALL_CONTENT = """\
filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)
"""

http_archive(
    name = "glfw",
    build_file_content = _ALL_CONTENT,
    strip_prefix = "glfw-3.3.8",
    sha256 = "f30f42e05f11e5fc62483e513b0488d5bceeab7d9c5da0ffe2252ad81816c713",
    url="https://github.com/glfw/glfw/archive/refs/tags/3.3.8.tar.gz",
)

maybe(
    http_archive,
    name="glew",
    url="https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.tar.gz",
)

maybe(
    http_archive,
    name="nuklear",
    url="https://github.com/Immediate-Mode-UI/Nuklear/archive/refs/tags/4.10.5.tar.gz",
)

git_repository(
    name="JesturePipe",
    remote="git@capstone-cs.eng.utah.edu:jesture/jesturepipe.git",
)