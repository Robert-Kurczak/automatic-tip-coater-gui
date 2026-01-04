#!/usr/bin/env python3

import sys
import subprocess
import os
import argparse
from dev import common
from dev import paths

def is_docker_image_built():
    result = subprocess.run(
        ["docker", "images", "-q", paths.STM32_BUILDER_IMAGE_NAME],
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
        check=False
    )
    return result.stdout != ""

def build_docker_image():
    common.log_info("=== Building docker image ===")

    try:
        subprocess.run(
            [
                "docker", "build",
                "--tag", paths.STM32_BUILDER_IMAGE_NAME,
                "--file", paths.STM32_BUILDER_DOCKERFILE_PATH,
                "."
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        common.log_error("=== Build failed ===")
        sys.exit(1)

    common.log_success("=== Build succeed ===")

def build_touchgfx_simulator(clean):
    try:
        build_command = f"bear  --output {paths.MOUNTED_COMPILE_COMMANDS_PATH} -- "
        build_command += f"make -f {paths.MOUNTED_TOUCHGFX_SIMULATOR_MAKEFILE_PATH} -j16"

        if clean:
            build_command += " clean"
        build_command += " all"

        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{paths.REPOSITORY_ROOT_PATH}:{paths.REPOSITORY_ROOT_MOUNT_PATH}:Z",
                paths.STM32_BUILDER_IMAGE_NAME,
                *build_command.split()
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        common.log_error("=== Build failed ===")
        sys.exit(1)

    common.log_success("=== Build succeed ===")


BUILD_TARGETS = {
    "touchgfx-simulator": build_touchgfx_simulator
}

def main(build_target_function, clean):
    if not is_docker_image_built():
        build_docker_image()

    build_target_function(clean)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="ATC Builder",
        description="Builds ATC targets inside the dev containers"
    )

    parser.add_argument(
        "build_target_name",
        type=str,
        help=f"""
            Name of the target to build.
            Available targets: {list(BUILD_TARGETS.keys())}
        """
    )

    parser.add_argument(
        "-c", "--clean",
        action="store_true",
        help="Clean target before build"
    )

    args = parser.parse_args()

    choosen_target = args.build_target_name
    build_target = BUILD_TARGETS.get(choosen_target)

    if build_target is None:
        print(f"Target '{choosen_target}' not found")
        print(f"Available targets: {list(BUILD_TARGETS.keys())}")
        sys.exit(1)

    main(build_target, args.clean)
