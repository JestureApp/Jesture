load("//qt:qt.bzl", "qt_resource")

package(default_visibility = ["//visibility:public"])

exports_files([
    "jesture.svg",
    "jesture.ico",
    "settings.svg",
])

qt_resource(
    name = "icons",
    files = {
        "jesture.svg": ":jesture.svg",
        "jesture.ico": ":jesture.ico",
        "settings.svg": ":settings.svg",
    },
    prefix = "/jesture/icons",
)
