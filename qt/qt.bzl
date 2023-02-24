"""
Qt Common Functions
"""

def qt_cc_library(
        name,
        srcs,
        moc_hdrs,
        hdrs = [],
        deps = None,
        copts = [],
        moc_args = [],
        **kwargs):
    """A macro that creates a Qt C++ library.

    Args:
        name (str): The name of the library target.
        srcs (_type_): _description_
        moc_hdrs (_type_): _description_
        hdrs (list, optional): _description_. Defaults to [].
        deps (_type_, optional): _description_. Defaults to None.
        copts (list, optional): _description_. Defaults to [].
        moc_args (list, optional): _description_. Defaults to [].
        **kwargs: _description_.
    """
    moc_srcs = []

    for hdr in moc_hdrs:
        # hdr_path = "%s/%s" % (native.package_name(), hdr)
        moc_name = "%s_moc" % hdr.replace(".", "_")
        native.genrule(
            name = moc_name,
            srcs = [hdr],
            outs = [moc_name + ".cc"],
            cmd = "$(location @qt//:moc) $< -o $@ -f $<",
            tools = ["@qt//:moc"],
        )

        moc_srcs.append(moc_name)

    native.cc_library(
        name = name,
        srcs = srcs + moc_srcs,
        hdrs = hdrs + moc_hdrs,
        copts = copts + select({
            "//conditions:default": ["-fPIC"],
        }),
        deps = deps,
    )
