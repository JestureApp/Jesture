workspace(name = "jesture")

################################################################################
# Development Dependencies
################################################################################

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Hedron's Compile Commands Extractor for Bazel
# https://github.com/hedronvision/bazel-compile-commands-extractor
http_archive(
    name = "hedron_compile_commands",
    sha256 = "085bde6c5212c8c1603595341ffe7133108034808d8c819f8978b2b303afc9e7",
    strip_prefix = "bazel-compile-commands-extractor-ed994039a951b736091776d677f324b3903ef939",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/ed994039a951b736091776d677f324b3903ef939.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

################################################################################
# Workspace Setup
################################################################################

load("//:repositories.bzl", "jesture_repositories")

jesture_repositories()

# SETUP STAGE 1
load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")
load("@bazel_skylib//lib:versions.bzl", "versions")
load("@jesture//qt:qt_configure.bzl", "qt_configure")
load("@jesturepipe//:repositories.bzl", "jesturepipe_repositories")
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

bazel_skylib_workspace()

rules_pkg_dependencies()

versions.check(
    maximum_bazel_version = "5.3.0",
    minimum_bazel_version = "5.0.0",
)

qt_configure()

jesturepipe_repositories()

# SETUP STAGE 2
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
load("@local_config_qt//:local_qt.bzl", "local_qt_base_path")
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
load("@org_tensorflow//tensorflow:workspace3.bzl", "tf_workspace3")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
load("@actions//:repositories.bzl", "actions_repositories")

maybe(
    new_local_repository,
    name = "qt",
    build_file = "@jesture//third_party:qt.BUILD",
    path = local_qt_base_path(),
)

register_toolchains(
    "@qt//:qt_local_toolchain",
)

rules_foreign_cc_dependencies()

protobuf_deps()

tf_workspace3()

actions_repositories()

# SETUP STAGE 3
load("@org_tensorflow//tensorflow:workspace2.bzl", "tf_workspace2")

tf_workspace2()

