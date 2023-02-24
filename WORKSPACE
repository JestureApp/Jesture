workspace(name = "jestureui")

# Load the bazel HTTP and GIT tools.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

maybe(
    git_repository,
    name = "rules_qt",
    remote = "https://github.com/Vertexwahn/rules_qt6",
    commit = "7814568b95dc6c1be420a5a844843404c793e316",
    shallow_since = "1671696880 +0100"
)

load("@rules_qt//:fetch_qt.bzl", "fetch_qt6")

fetch_qt6()

load("@rules_qt//tools:qt_toolchain.bzl", "register_qt_toolchains")

register_qt_toolchains()

maybe(
    http_archive,
    name = "glfw",
    build_file = "//third_party:glfw.BUILD",
    strip_prefix = "glfw-3.3.8",
    sha256 = "f30f42e05f11e5fc62483e513b0488d5bceeab7d9c5da0ffe2252ad81816c713",
    url="https://github.com/glfw/glfw/archive/refs/tags/3.3.8.tar.gz",
)

maybe(
    http_archive,
    name = "json",
    build_file = "//third_party:json.BUILD",
    strip_prefix = "json-3.11.2",
    url = "https://github.com/nlohmann/json/archive/v3.11.2.tar.gz",
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

maybe(
    new_local_repository,
    name = "platform_folders",
    build_file = "//third_party/platform_folders:BUILD",
    path = "third_party/platform_folders",
)