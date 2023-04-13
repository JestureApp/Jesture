load("@local_config_qt//:local_qt.bzl", "qt_module", "register_toolchain")

################################################################################
# Toolchains
################################################################################

toolchain_type(name = "toolchain_type")

register_toolchain()

toolchain(
    name = "qt_local_toolchain",
    toolchain = ":qt_local",
    toolchain_type = ":toolchain_type",
)

################################################################################
# Qt Modules
################################################################################

# qt_core
qt_module(
    name = "qt_core",
    include_dir = "QtCore",
    lib = "Qt6Core",
)

# qt_gui
qt_module(
    name = "qt_gui",
    include_dir = "QtGui",
    lib = "Qt6Gui",
    deps = [
        ":qt_core",
    ],
)

# qt_multimedia
qt_module(
    name = "qt_multimedia",
    include_dir = "QtMultimedia",
    lib = "Qt6Multimedia",
    deps = [
        ":qt_core",
        ":qt_gui",
        ":qt_network",
    ],
)

# qt_multimedia_widgets
qt_module(
    name = "qt_multimedia_widgets",
    include_dir = "QtMultimediaWidgets",
    lib = "Qt6MultimediaWidgets",
    deps = [
        ":qt_core",
    ],
)

# qt_network
qt_module(
    name = "qt_network",
    include_dir = "QtNetwork",
    lib = "Qt6Network",
    deps = [
        ":qt_core",
    ],
)

# qt_opengl
qt_module(
    name = "qt_opengl",
    include_dir = "QtOpenGL",
    lib = "Qt6OpenGL",
    deps = [
        ":qt_core",
        ":qt_gui",
    ],
)

# qt_qml
qt_module(
    name = "qt_qml",
    include_dir = "QtQml",
    lib = "Qt6Qml",
    deps = [
        ":qt_core",
        ":qt_network",
        ":qt_qml_integration",
    ],
)

# qt_qml_integration
qt_module(
    name = "qt_qml_integration",
    include_dir = "QtQmlIntegration",
    deps = [
        ":qt_core",
    ],
)

# qt_qml_models
qt_module(
    name = "qt_qml_models",
    include_dir = "QtQmlModels",
    lib = "Qt6QmlModels",
    deps = [
        ":qt_core",
        ":qt_qml",
    ],
)

qt_module(
    name = "qt_qml_workerscript",
    include_dir = "QtQmlWorkerScript",
    lib = "Qt6QmlWorkerScript",
    deps = [
        ":qt_core",
        ":qt_qml",
    ],
)

# qt_quick
qt_module(
    name = "qt_quick",
    include_dir = "QtQuick",
    lib = "Qt6Quick",
    deps = [
        ":qt_core",
        ":qt_gui",
        ":qt_opengl",
        ":qt_qml",
        ":qt_qml_models",
    ],
)

# qt_widgets
qt_module(
    name = "qt_widgets",
    include_dir = "QtWidgets",
    lib = "Qt6Widgets",
    deps = [
        ":qt_core",
        ":qt_gui",
    ],
)

################################################################################
# Binaries
################################################################################

# add_binary(name = "moc")
