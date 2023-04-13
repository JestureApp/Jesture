"""
TODO
"""

load("@rules_pkg//pkg:providers.bzl", "PackageVariablesInfo")
load("@rules_cc//cc:find_cc_toolchain.bzl", "find_cc_toolchain")

def _dist_vars_impl(ctx):
    values = {}

    # cc_toolchain = find_cc_toolchain(ctx)

    values["product_name"] = ctx.attr.product_name
    values["version"] = ctx.attr.version.replace(".", "_")

    values["arch"] = ctx.attr.arch

    return PackageVariablesInfo(values = values)

dist_vars = rule(
    implementation = _dist_vars_impl,
    attrs = {
        "product_name": attr.string(
            doc = "Placeholder for our final product name.",
        ),
        "version": attr.string(
            doc = "Placeholder for our release version.",
        ),
        "arch": attr.string(),
        "_cc_toolchain": attr.label(
            default = Label(
                "@rules_cc//cc:current_cc_toolchain",
            ),
        ),
    },
    toolchains = ["@rules_cc//cc:toolchain_type"],
    incompatible_use_toolchain_transition = True,
)
