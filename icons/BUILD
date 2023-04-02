load("//qt:qt.bzl", "qt_resource")

package(default_visibility = ["//visibility:public"])

exports_files([
    "jesture.svg",
    "jesture.ico",
])

qt_resource(
    name = "icons",
    files = {
        "jesture.svg": ":jesture.svg",
        "jesture.ico": ":jesture.ico",
    },
    prefix = "/jesture/icons",
)
