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

load("//:setup0.bzl", "jesture_setup0")

jesture_setup0()

load("//:setup1.bzl", "jesture_setup1")

jesture_setup1()
