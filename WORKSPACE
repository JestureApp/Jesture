workspace(name = "jestureui")

# Load the bazel HTTP and GIT tools.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

maybe(
    http_archive,
    name = "glfw",
    build_file = "//third_party:glfw.BUILD",
    strip_prefix = "glfw-3.3.8",
    sha256 = "f30f42e05f11e5fc62483e513b0488d5bceeab7d9c5da0ffe2252ad81816c713",
    url="https://github.com/glfw/glfw/archive/refs/tags/3.3.8.tar.gz",
)

maybe(
    new_local_repository,
    name = "glfw_macos",
    build_file = "//third_party:glfw_macos.BUILD",
    path = "/opt/homebrew",
)

maybe(
    new_local_repository,
    name = "glad",
    build_file = "//third_party/glad:BUILD",
    path = "third_party/glad",
)

maybe(
    new_local_repository,
    name = "nuklear",
    build_file = "//third_party/nuklear:BUILD",
    path = "third_party/nuklear",
)