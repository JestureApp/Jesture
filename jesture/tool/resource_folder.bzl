"""
Utility for creating resource folders
"""

load("@bazel_skylib//lib:paths.bzl", "paths")

def resource_folder(
        name,
        dir_name,
        file_targets):
    """Creates a resource folder

    Args:
        name (str): The name of the filegroup target
        dir_name (str): The directory to create
        file_targets (dict): mapping form files to create to their targets
    """

    # native.genrule(
    #     name = name + "_dir",
    #     outs = [dir_name],
    #     cmd = "mkdir -p $@",
    # )

    files = []

    for file, target in file_targets.items():
        gen_name = name + "_" + file.replace(".", "_")

        native.genrule(
            name = gen_name,
            srcs = [target],
            outs = [paths.join(dir_name, file)],
            output_to_bindir = 1,
            cmd = "ln $< $@",
        )

        files.append(gen_name)

    native.filegroup(
        name = name,
        srcs = files,
    )
