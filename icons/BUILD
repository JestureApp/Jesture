load("//qt:qt.bzl", "qt_resource")

package(default_visibility = ["//visibility:public"])

exports_files([
    "settings.svg",
    "show.svg",
    "hide.svg",
    "quit.svg",
    "add_element.svg",
    "cross.svg",
    "left_arrow.svg",
    "add.svg",
    "Jesture.svg",
])

qt_resource(
    name = "icons",
    files = {
        "jesture.png": ":Jesture.png",
        "jesture.svg": ":Jesture.svg",
        "jesture.ico": ":Jesture.ico",
        "settings.svg": ":settings.svg",
        "show.svg": ":show.svg",
        "hide.svg": ":hide.svg",
        "quit.svg": ":quit.svg",
        "add_element.svg": ":add_element.svg",
        "cross.svg": ":cross.svg",
        "left_arrow.svg": ":left_arrow.svg",
        "add.svg": ":add.svg",
    },
    # prefix = "/jesture/icons",
)
