#!/usr/bin/env python3

import os
import subprocess
import sys
from pathlib import Path
import argparse

STM32_BUILDER_IMAGE_NAME = "atc-stm32-builder"

DOCKERFILE_PATH = Path(__file__).joinpath(
    f"docker/{STM32_BUILDER_IMAGE_NAME}.dockerfile"
)

REPOSITORY_ROOT_DIR = Path(__file__).parent.parent

REPOSITORY_ROOT_MOUNT_PATH = Path("/atc")

APPLICATION_MOUNT_PATH = REPOSITORY_ROOT_MOUNT_PATH.joinpath(
    "application/"
)

SIMULATOR_MAKEFILE_MOUNT_PATH = REPOSITORY_ROOT_MOUNT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
)

def is_docker_image_built():
    result = subprocess.run(
        ["docker", "images", "-q", STM32_BUILDER_IMAGE_NAME],
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
        check=False
    )
    return result.stdout != ""

def build_docker_image():
    print("=== Building docker image ===")

    try:
        subprocess.run(
            [
                "docker", "build",
                "--tag", STM32_BUILDER_IMAGE_NAME,
                "--file", DOCKERFILE_PATH,
                "."
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        print("=== Build failed ===")
        sys.exit(1)

    print("=== Build succeed ===")

def build_touchgfx_simulator():
    try:
        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{REPOSITORY_ROOT_DIR}:{REPOSITORY_ROOT_MOUNT_PATH}:Z",
                "--env", f"ADDITIONAL_SOURCES_DIR={APPLICATION_MOUNT_PATH}",
                "--env", f"ADDITIONAL_INCLUDE_DIR={REPOSITORY_ROOT_MOUNT_PATH}",
                STM32_BUILDER_IMAGE_NAME,
                "make", "-f", SIMULATOR_MAKEFILE_MOUNT_PATH, "clean"
            ],
            check=True
        )

        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{REPOSITORY_ROOT_DIR}:{REPOSITORY_ROOT_MOUNT_PATH}:Z",
                "--env", f"ADDITIONAL_SOURCES_DIR={APPLICATION_MOUNT_PATH}",
                "--env", f"ADDITIONAL_INCLUDE_DIR={REPOSITORY_ROOT_MOUNT_PATH}",
                STM32_BUILDER_IMAGE_NAME,
                "make", "-j16", "-f", SIMULATOR_MAKEFILE_MOUNT_PATH, "clean", "all"
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        print("=== Build failed ===")
        sys.exit(1)

    print("=== Build succeed ===")


BUILD_TARGETS = {
    "touchgfx-simulator": build_touchgfx_simulator
}

def main(build_target_function):
    if not is_docker_image_built():
        build_docker_image()

    build_target_function()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="ATC Builder",
        description="Builds ATC targets inside the dev containers"
    )

    parser.add_argument(
        "build_target_name",
        help=f"""
            Name of the target to build.
            Available targets: {list(BUILD_TARGETS.keys())}
        """
    )
    args = parser.parse_args()

    choosen_target = args.build_target_name
    build_target = BUILD_TARGETS.get(args.build_target_name)

    if build_target is None:
        print(f"Target '{choosen_target}' not found")
        print(f"Available targets: {list(BUILD_TARGETS.keys())}")
        sys.exit(1)

    main(build_target)
