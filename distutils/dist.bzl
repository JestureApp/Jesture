"""
TODO
"""

load("@rules_pkg//pkg:providers.bzl", "PackageVariablesInfo")
load("@rules_pkg//pkg:mappings.bzl", "pkg_attributes", "pkg_files", "pkg_mklink")
load("@rules_pkg//pkg:deb.bzl", "pkg_deb")
load("@rules_pkg//pkg:tar.bzl", "pkg_tar")

def _naming_vars_impl(ctx):
    values = {}

    # Copy attributes from the rule to the provider
    values["product_name"] = ctx.attr.product_name
    values["version"] = ctx.attr.version

    # Add some well known variables from the rule context.
    values["target_arch"] = ctx.var.get("TARGET_ARCH")

    return PackageVariablesInfo(values = values)

naming_vars = rule(
    implementation = _naming_vars_impl,
    attrs = {
        "product_name": attr.string(
            doc = "Placeholder for our final product name.",
        ),
        "version": attr.string(
            doc = "Placeholder for our release version.",
        ),
    },
)

def distribution(
        name,
        product_name,
        version,
        deb_package_name,
        deb_package_desc,
        maintainer,
        bin):
    naming_vars(
        name = name + "_pkg_vars",
        product_name = product_name,
        version = version,
    )

    pkg_files(
        name = name + "_linux_bin",
        srcs = [bin],
        renames = {
            bin: product_name,
        },
        attributes = pkg_attributes(
            mode = "0551",
        ),
        prefix = "/opt/%s" % product_name,
    )

    pkg_mklink(
        name = name + "_linux_usr_bin",
        link_name = "/usr/bin/%s" % product_name,
        target = "/opt/%s/%s" % (product_name, product_name),
    )

    pkg_tar(
        name = name + "_linux",
        srcs = [
            name + "_linux_bin",
            name + "_linux_usr_bin",
        ],
        package_file_name = "{product_name}.tar",
        package_variables = name + "_pkg_vars",
    )

    pkg_deb(
        name = name + "_deb",
        data = name + "_linux",
        package = deb_package_name,
        description = deb_package_desc,
        package_file_name = "{product_name}.deb",
        package_variables = name + "_pkg_vars",
        maintainer = maintainer,
        version = version,
    )

    native.filegroup(
        name = name,
        srcs = [
            name + "_linux",
            name + "_deb",
        ],
    )
