"""
Rules for setting up qt in the workspace 
"""

def _get_env_var(repository_ctx, name, default = None):
    """Returns a value from an environment variable."""
    for key, value in repository_ctx.os.environ.items():
        if name == key:
            return value
    return default

def qt_autoconf_impl(repository_ctx):
    """
    Generate BUILD file with 'local_qt_path' function to get the Qt local path.

    Args:
       repository_ctx: repository context
    """
    os_name = repository_ctx.os.name.lower()
    is_linux_machine = False
    
    if os_name.find("linux") != -1:
        is_linux_machine = True
        
        default_qt_path = "/usr/include/qt6"
    elif os_name.find("mac") != -1:
        # assume Qt was installed using `brew install qt@5`
        default_qt_path = "/usr/local/opt/qt@6"

        if not repository_ctx.path(default_qt_path).exists:
            default_qt_path = "/opt/homebrew/include"
    else:
        fail("Unsupported OS: %s" % os_name)

    if repository_ctx.path(default_qt_path).exists:
        # buildifier: disable=print
        print("Installation available on the default path: ", default_qt_path)

    qt_path = _get_env_var(repository_ctx, "BAZEL_RULES_QT_DIR", default_qt_path)
    if qt_path != default_qt_path:
        # buildifier: disable=print
        print("However BAZEL_RULES_QT_DIR is defined and will be used: ", qt_path) # ignore: print

        # In Linux in case that we have a standalone installation, we need to provide the path inside the include folder
        qt_path_with_include = qt_path + "/include"
        if is_linux_machine and repository_ctx.path(qt_path_with_include).exists:
            qt_path = qt_path_with_include
   
    repository_ctx.file("BUILD", "# empty BUILD file so that bazel sees this as a valid package directory")
    repository_ctx.template(
        "local_qt.bzl",
        repository_ctx.path(Label("@jesture//qt:BUILD.local_qt.tpl")),
        {"%{path}": qt_path},
    )

qt_autoconf = repository_rule(
    implementation = qt_autoconf_impl,
    configure = True,
)

def qt_configure():
    qt_autoconf(name = "local_config_qt")
