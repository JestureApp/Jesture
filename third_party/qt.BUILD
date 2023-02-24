load("@local_config_qt//:local_qt.bzl", "qt_module")

qt_module(
    name = "qt_core",
    include_dir = "QtCore",
    lib = "Qt6Core",
)


qt_module(
    name = "qt_gui",
    include_dir = "QtGui",
    lib = "Qt6Gui",
    deps = [
        ":qt_core",
    ]
)

qt_module(
    name = "qt_widgets",
    include_dir = "QtWidgets",
    lib = "Qt6Widgets",
    deps = [
        ":qt_core",
        ":qt_gui",
    ]
)


qt_module(
    name = "qt_multimedia",
    include_dir = "QtMultimedia",
    lib = "Qt6Multimedia",
    deps = [
        ":qt_core",
    ]
)

qt_module(
    name = "qt_multimedia_widgets",
    include_dir = "QtMultimediaWidgets",
    lib = "Qt6MultimediaWidgets",
    deps = [
        ":qt_core",
    ]
)
