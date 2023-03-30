"""
TODO
"""

def app(
        name,
        bin_srcs,
        bin_deps = []):
    native.cc_binary(
        name = name,
        srcs = bin_srcs,
        deps = bin_deps,
        copts = ["-fPIC"],
    )
