"""
Qt Common Functions

Derived from:
 - https://github.com/justbuchanan/bazel_rules_qt
 - https://github.com/Vertexwahn/rules_qt6
"""

# TODO: make Qt plugin available

# TODO: make Qt qml lib files available

# TODO: Add macro for qml

def _qt_moc_impl(ctx):
    toolchain_info = ctx.toolchains["@qt//:toolchain_type"].qtinfo

    hdr_file = ctx.files.hdr[0]
    out_file = ctx.outputs.out

    arguments = [hdr_file.path, "-o", out_file.path, "-f", hdr_file.path] + ctx.attr.args

    ctx.actions.run(
        inputs = [hdr_file],
        outputs = [out_file],
        arguments = arguments,
        executable = toolchain_info.moc,
    )

    return [OutputGroupInfo(out = depset([out_file]))]
    # pass

qt_moc = rule(
    implementation = _qt_moc_impl,
    attrs = {
        "hdr": attr.label(
            doc = "Header file to read from",
            allow_single_file = [".h", ".hpp"],
            mandatory = True,
        ),
        "out": attr.output(
            doc = "File to write output to",
            mandatory = True,
        ),
        "args": attr.string_list(
            doc = "Additional arguments to pass to moc",
            mandatory = False,
            default = [],
        ),
    },
    toolchains = ["@qt//:toolchain_type"],
)

def qt_cc_library(
        name,
        moc_hdrs = [],
        srcs = [],
        hdrs = [],
        copts = [],
        moc_args = [],
        **kwargs):
    """A macro that creates a Qt C++ library.

    Args:
        name: The name of the library target.
        srcs: The source c++ files
        moc_hdrs: Any headers that must be compiled with moc.
        hdrs: Any headers that do not need to be compiled with moc. Defaults to [].
        copts: Any compiler options compatible with cc_library. Defaults to [].
        moc_args: Any arguments to pass to the moc compiler. Defaults to [].
        **kwargs: Addition arguments passed to cc_library.
    """
    # moc_srcs = _compile_moc_hdrs(moc_hdrs, moc_args)

    moc_srcs = []

    for hdr in moc_hdrs:
        moc_name = "%s_moc" % hdr.replace(".", "_")

        qt_moc(
            name = moc_name,
            hdr = hdr,
            out = moc_name + ".cc",
        )

        moc_srcs.append(moc_name)

    native.cc_library(
        name = name,
        srcs = srcs + moc_srcs,
        hdrs = hdrs + moc_hdrs,
        copts = copts + select({
            "@platforms//os:windows": [],
            "//conditions:default": ["-fPIC"],
        }),
        **kwargs
    )

def qt_cc_binary(
        name,
        copts = [],
        **kwargs):
    native.cc_binary(
        name = name,
        copts = copts + select({
            "@platforms//os:windows": [],
            "//conditions:default": ["-fPIC"],
        }),
        **kwargs
    )

def qt_resource(
        name,
        files):
    pass
