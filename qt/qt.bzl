"""
Qt Common Functions

Derived from:
 - https://github.com/justbuchanan/bazel_rules_qt
 - https://github.com/Vertexwahn/rules_qt6
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

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

def _qt_qrc_impl(ctx):
    out = ctx.outputs.out

    prefix = ctx.attr.prefix

    content = "<RCC>\n\t<qresource prefix=\\\"%s\\\">" % prefix

    inputs = []

    for t, alias in ctx.attr.data.items():
        files = t.files.to_list()

        if (len(files) != 1):
            fail("Each data target must have exactly one file. %s has %d files" % (t, len(files)))

        file = files[0]

        prefixed_file_path = paths.join(ctx.attr.resource_link_prefix, file.path)
        input = ctx.actions.declare_file(prefixed_file_path)
        ctx.actions.symlink(
            output = input,
            target_file = file,
        )

        inputs.append(input)

        content += "\n\t\t<file alias=\\\"%s\\\">%s</file>" % (alias, prefixed_file_path)

    content += "\n\t</qresource>\n</RCC>"

    cmd = ["echo", '"%s"' % content, ">", out.path]

    execution_requirements = {}
    for elem in ctx.attr.tags:
        execution_requirements[elem] = "1"

    ctx.actions.run_shell(
        command = " ".join(cmd),
        # inputs = inputs,
        outputs = [out],
        execution_requirements = execution_requirements,
    )

    return [OutputGroupInfo(qrc = depset([out]))]

qt_qrc = rule(
    implementation = _qt_qrc_impl,
    attrs = {
        "data": attr.label_keyed_string_dict(
            doc = "Data Files to add to qrc file",
            allow_files = True,
            mandatory = True,
        ),
        "prefix": attr.string(
            doc = "The prefix for the qrc file",
            mandatory = False,
            default = "/",
        ),
        "out": attr.output(mandatory = True),
        "resource_link_prefix": attr.string(
            mandatory = False,
            default = "_resources",
        ),
    },
)

def _qt_rcc_impl(ctx):
    toolchain_info = ctx.toolchains["@qt//:toolchain_type"].qtinfo

    inputs = []
    for f in ctx.files.files:
        prefixed_file_path = paths.join(ctx.attr.resource_link_prefix, f.path)

        input = ctx.actions.declare_file(prefixed_file_path)
        ctx.actions.symlink(
            output = input,
            target_file = f,
        )

        inputs.append(input)

    args = [
        "--name",
        ctx.attr.resource_name,
        "--output",
        ctx.outputs.out.path,
        ctx.file.qrc.path,
    ]

    execution_requirements = {}
    for elem in ctx.attr.tags:
        execution_requirements[elem] = "1"

    ctx.actions.run(
        inputs = [ctx.file.qrc] + inputs,
        outputs = [ctx.outputs.out],
        arguments = args,
        executable = toolchain_info.rcc,
        execution_requirements = execution_requirements,
    )

    return [OutputGroupInfo(out = depset([ctx.outputs.out]))]

qt_rcc = rule(
    implementation = _qt_rcc_impl,
    attrs = {
        "resource_name": attr.string(
            doc = "Create an external initialization function with <name>",
            mandatory = True,
        ),
        "qrc": attr.label(allow_single_file = True, mandatory = True),
        "files": attr.label_list(allow_files = True, mandatory = False),
        "out": attr.output(mandatory = True),
        "resource_link_prefix": attr.string(
            mandatory = False,
            default = "_resources",
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
            args = moc_args,
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
        files,
        prefix = "/",
        deps = [],
        **kwargs):
    """_summary_

    Args:
        name (_type_): _description_
        files (_type_): _description_
        prefix (str, optional): _description_. Defaults to "/".
        deps: _description_. Defaults to [].
        **kwargs: _description_
    """
    data = {f: a for a, f in files.items()}

    qrc_file = name + "_qrc.qrc"

    qt_qrc(
        name = name + "_qrc",
        data = data,
        prefix = prefix,
        out = qrc_file,
    )

    file_targets = files.values()
    gen_file = name + "_gen.cpp"
    resource_name = native.package_name().replace("/", "_") + "_" + name

    qt_rcc(
        name = name + "_gen",
        resource_name = resource_name,
        files = file_targets,
        qrc = qrc_file,
        out = gen_file,
        tags = ["local"],
    )

    native.cc_library(
        name = name,
        srcs = [gen_file],
        alwayslink = 1,
        deps = [
            "@qt//:qt_core",
        ] + deps,
        **kwargs
    )

    pass
