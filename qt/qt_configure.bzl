"""
Rules for setting up qt in the workspace 
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

# Possible paths are tried in order
# Structured as (repository path, include directory, library directory, binary directory)
possible_linux_installs = [
    ("/usr", "include/qt6", "lib", "lib/qt6"),
    ("/usr", "include/qt6", "lib", "bin"),
]

possible_osx_installs = [
    ("/usr/local/opt/qt@6", "include", "lib", "share/qt/libexec"),
    ("/opt/homebrew", "include", "lib", "share/qt/libexec"),
]

def _validate_install(install, repository_ctx):
    base, inc, lib, bin = install

    inc_abs = paths.join(base, inc)
    lib_abs = paths.join(base, lib)
    bin_abs = paths.join(base, bin)

    if not repository_ctx.path(inc_abs).exists or \
       not repository_ctx.path(lib_abs).exists or \
       not repository_ctx.path(bin_abs).exists:
        return False

    moc_path = paths.join(bin_abs, "moc")
    if not repository_ctx.path(moc_path).exists:
        return False

    res = repository_ctx.execute([moc_path, "--version"])
    if res.return_code != 0 or res.stdout.index("6.") == -1:
        return False

    return True

def auto_detect_qt_path(repository_ctx):
    """
    Detects the path to the Qt installation.

    Args:
       repository_ctx: repository context

    Returns:
       (include_path, lib_path)
    """

    os_name = repository_ctx.os.name.lower()

    if os_name.find("linux") != -1:
        possible_installs = possible_linux_installs
    elif os_name.find("mac") != -1:
        possible_installs = possible_osx_installs
    else:
        fail("Unsupported OS: %s" % os_name)

    install = None

    for inst in possible_installs:
        if _validate_install(inst, repository_ctx):
            install = inst
            break

    return install

def qt_autoconf_impl(repository_ctx):
    """
    Generate BUILD file with 'local_qt_path' function to get the Qt local path.

    Args:
       repository_ctx: repository context
    """

    install = auto_detect_qt_path(repository_ctx)

    if not install:
        fail("Failed to detect viable Qt6 installation.")

    base, inc, lib, bin = install

    repository_ctx.file("BUILD", "# empty BUILD file so that bazel sees this as a valid package directory")
    repository_ctx.template(
        "local_qt.bzl",
        repository_ctx.path(Label("@jesture//qt:BUILD.local_qt.tpl.bzl")),
        {
            "${base_path}": base,
            "${include_path}": inc,
            "${lib_path}": lib,
            "${bin_path}": bin,
        },
    )

qt_autoconf = repository_rule(
    implementation = qt_autoconf_impl,
    configure = True,
)

def qt_configure():
    qt_autoconf(name = "local_config_qt")
