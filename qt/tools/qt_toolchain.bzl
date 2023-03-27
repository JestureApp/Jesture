"""
Toolchains for Qt
"""

QtToolchainInfo = provider(
    doc = "Information about how to invoke qt tools.",
    fields = ["rcc", "moc"],
)

def _qt_toolchain_impl(ctx):
    toolchain_info = platform_common.ToolchainInfo(
        qtinfo = QtToolchainInfo(
            rcc = ctx.attr.rcc,
            moc = ctx.attr.moc,
        ),
    )

    return [toolchain_info]

qt_toolchain = rule(
    implementation = _qt_toolchain_impl,
    attrs = {
        "rcc": attr.string(),
        "moc": attr.string(),
    },
)
