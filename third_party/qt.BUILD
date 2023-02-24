load("@rules_cc//cc:defs.bzl", "cc_import", "cc_library")

QT_LIBRARIES = [
    ("core", "QtCore", "Qt6Core", []),
    ("network", "QtNetwork", "Qt6Network", []),
    ("widgets", "QtWidgets", "Qt6Widgets", [":qt_core", ":qt_gui"]),
    ("quick", "QtQuick", "Qt6Quick", [":qt_gui", ":qt_qml"]),
    ("qml", "QtQml", "Qt6Qml", [":qt_core", ":qt_network"]),
    ("qml_models", "QtQmlModels", "Qt5QmlModels", []),
    ("gui", "QtGui", "Qt6Gui", [":qt_core"]),
    ("opengl", "QtOpenGL", "Qt6OpenGL", []),
    ("multimedia", "QtMultimedia", "Qt6Multimedia", [":qt_core"]),
    ("multimedia_widgets", "QtMultimediaWidgets", "Qt6MultimediaWidgets", []),
]

[
    cc_library(
        name = "qt_%s_linux" % name,
        # When being on Windows this glob will be empty
        hdrs = glob(["%s/**" % include_folder], allow_empty = True),
        includes = ["."],
        linkopts = ["-l%s" % library_name],
        # Available from Bazel 4.0.0
        # target_compatible_with = ["@platforms//os:linux"],
    )
    for name, include_folder, library_name, _ in QT_LIBRARIES
]

[
    cc_import(
        name = "qt_%s_windows_import" % name,
        # When being on Linux or macOS this glob will be empty
        hdrs = glob(["include/%s/**" % include_folder], allow_empty = True),
        interface_library = "lib/%s.lib" % library_name,
        shared_library = "bin/%s.dll" % library_name,
        # Not available in cc_import (See: https://github.com/bazelbuild/bazel/issues/12745)
        # target_compatible_with = ["@platforms//os:windows"],
    )
    for name, include_folder, library_name, _ in QT_LIBRARIES
]

[
    cc_library(
        name = "qt_%s_windows" % name,
        # When being on Linux or macOS this glob will be empty
        hdrs = glob(["include/%s/**" % include_folder], allow_empty = True),
        includes = ["include"],
        # Available from Bazel 4.0.0
        # target_compatible_with = ["@platforms//os:windows"],
        deps = [":qt_%s_windows_import" % name],
    )
    for name, include_folder, _, _ in QT_LIBRARIES
]

[
    cc_library(
        name = "qt_%s_osx" % name,
        # When being on Windows or Linux this glob will be empty
        hdrs = glob(["%s/**" % include_folder], allow_empty = True),
        includes = ["."],
        linkopts = ["-F/usr/local/opt/qt6/lib", "-F/opt/homebrew/lib"] + [
            "-framework %s" % library_name.replace("6", "") # macOS qt libs do not contain a 6 - e.g. instead of Qt5Core the lib is called QtCore
        ],
        # Available from Bazel 4.0.0
        # target_compatible_with = ["@platforms//os:osx"],
    )
    for name, include_folder, library_name, _ in QT_LIBRARIES
]

[
    cc_library(
        name = "qt_%s" % name,
        visibility = ["//visibility:public"],
        deps = dependencies + select({
            "@platforms//os:linux": [":qt_%s_linux" % name],
            "@platforms//os:windows": [":qt_%s_windows" % name],
            "@platforms//os:osx": [":qt_%s_osx" % name],
        }),
    )
    for name, _, _, dependencies in QT_LIBRARIES
]

cc_library(
    name = "qt_3d",
    # When being on Windows this glob will be empty
    hdrs = glob([
        "Qt3DAnimation/**",
        "Qt3DCore/**",
        "Qt3DExtras/**",
        "Qt3DInput/**",
        "Qt3DLogic/**",
        "Qt3DQuick/**",
        "Qt3DQuickAnimation/**",
        "Qt3DQuickExtras/**",
        "Qt3DQuickInput/**",
        "Qt3DQuickRender/**",
        "Qt3DQuickScene2D/**",
        "Qt3DRender/**",
    ], allow_empty = True),
    includes = ["."],
    linkopts = [
        "-lQt53DAnimation",
        "-lQt53DCore",
        "-lQt53DExtras",
        "-lQt53DInput",
        "-lQt53DLogic",
        "-lQt53DQuick",
        "-lQt53DQuickAnimation",
        "-lQt53DQuickExtras",
        "-lQt53DQuickInput",
        "-lQt53DQuickRender",
        "-lQt53DQuickScene2D",
        "-lQt53DRender",
    ],
    # Available from Bazel 4.0.0
    target_compatible_with = ["@platforms//os:linux"],
)
