"""
Rules for setting up qt in the workspace 
"""

def auto_detect_qt_path(repository_ctx):
    """
    Detects the path to the Qt installation.

    Args:
       repository_ctx: repository context

    Returns:
       (include_path, lib_path)
    """

    os_name = repository_ctx.os.name.lower()

    if os_name.find("linux")!= -1:
        possible_include_paths = [
            "/usr/include/qt6"
        ]

        possible_lib_paths = [
            "/usr/lib"
        ]
    elif os_name.find("mac")!= -1:
        possible_include_paths = [
            "/usr/local/opt/qt@6", 
            "/opt/homebrew/include"
        ]
        possible_lib_paths = [
            "/usr/local/opt/qt6/lib", 
            "/opt/homebrew/lib"
        ]
    else:
        fail("Unsupported OS: %s" % os_name)

    include_path = None

    for path in possible_include_paths:
        if repository_ctx.path(path).exists:
            include_path = path
            break

    lib_path = None

    for path in possible_lib_paths:
        if repository_ctx.path(path).exists:
            lib_path = path
            break

    return include_path, lib_path

def qt_autoconf_impl(repository_ctx):
    """
    Generate BUILD file with 'local_qt_path' function to get the Qt local path.

    Args:
       repository_ctx: repository context
    """

    include_path, lib_path = auto_detect_qt_path(repository_ctx)

    if not include_path or not repository_ctx.path(include_path).exists:
        fail("Qt include directory %s does not exist" % include_path)

    if not lib_path or not repository_ctx.path(lib_path).exists:
        fail("Qt include directory %s does not exist" % lib_path)
   
    repository_ctx.file("BUILD", "# empty BUILD file so that bazel sees this as a valid package directory")
    repository_ctx.template(
        "local_qt.bzl",
        repository_ctx.path(Label("@jesture//qt:BUILD.local_qt.tpl.bzl")),
        {
            "${include_path}": include_path,
            "${lib_path}": lib_path,
        },
    )

qt_autoconf = repository_rule(
    implementation = qt_autoconf_impl,
    configure = True,
)

def qt_configure():
    qt_autoconf(name = "local_config_qt")
