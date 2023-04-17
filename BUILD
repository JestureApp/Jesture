load("//distribution:dist_vars.bzl", "dist_vars")
load("@rules_pkg//pkg:mappings.bzl", "pkg_attributes", "pkg_files", "pkg_mklink")
load("@rules_pkg//pkg:deb.bzl", "pkg_deb")
load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

VERSION = "0.5.0"

dist_vars(
    name = "jesture_dist_vars",
    arch = select({
        "@platforms//cpu:x86_64": "x86_64",
        "//conditions:default": "UNKNOWN",
    }),
    product_name = "jesture",
    version = VERSION,
)

pkg_files(
    name = "jesture_linux_bin",
    srcs = ["//jesture"],
    attributes = pkg_attributes(
        mode = "0551",
    ),
    prefix = "/opt/jesture",
)

pkg_files(
    name = "jesture_linux_models",
    srcs = ["//jesture:models"],
    prefix = "/opt/jesture/models",
)

pkg_mklink(
    name = "jesture_linux_usr_bin",
    link_name = "/usr/bin/jesture",
    target = "/opt/jesture/jesture",
)

pkg_tar(
    name = "jesture_linux_tar",
    srcs = [
        ":jesture_linux_bin",
        ":jesture_linux_models",
        ":jesture_linux_usr_bin",
    ],
    package_file_name = "{product_name}-{version}-{arch}-linux.tar",
    package_variables = ":jesture_dist_vars",
)

pkg_deb(
    name = "jesture_deb",
    data = ":jesture_linux_tar",
    depends = [
        "qt6-base-dev",
        "qt6-wayland",
        "qt6-declarative-dev",
        "qt6-multimedia-dev",
        "libqt6svg6-dev",
        "libx11-dev",
        "libopencv-dev",
    ],
    description = "Application to control you computer through hand gestures",
    maintainer = "carson.storm@outlook.com",
    package = "jesture",
    package_file_name = "{product_name}-{version}-{arch}.deb",
    package_variables = ":jesture_dist_vars",
    version = VERSION,
)

filegroup(
    name = "distribution",
    srcs = [
        ":jesture_deb",
        ":jesture_linux_tar",
    ],
)
