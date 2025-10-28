#!/usr/bin/env python3

import os
import subprocess
import sys
from pathlib import Path
import argparse

IMAGE_NAME = "atc-stm32-builder"

PROJECT_ROOT_DIR = Path(__file__).parent.parent.parent.parent
PROJECT_ROOT_MOUNT_PATH = Path("/project")

APPLICATION_MOUNT_PATH = PROJECT_ROOT_MOUNT_PATH.joinpath(
    "application/"
)

SIMULATOR_MAKEFILE_MOUNT_PATH = PROJECT_ROOT_MOUNT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
)

DOCKERFILE_PATH = Path(__file__).parent.joinpath("Dockerfile")

def is_docker_image_built():
    result = subprocess.run(
        ["docker", "images", "-q", IMAGE_NAME],
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
                "--tag", IMAGE_NAME,
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
                "--volume", f"{PROJECT_ROOT_DIR}:{PROJECT_ROOT_MOUNT_PATH}:Z",
                "--env", f"ADDITIONAL_SOURCES_DIR={APPLICATION_MOUNT_PATH}",
                "--env", f"ADDITIONAL_INCLUDE_DIR={PROJECT_ROOT_MOUNT_PATH}",
                IMAGE_NAME,
                "make", "-f", SIMULATOR_MAKEFILE_MOUNT_PATH, "-j16"
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        print("=== Build failed ===")
        sys.exit(1)

    print("=== Build succeed ===")


BUILD_TARGETS = {
    "simulator": build_touchgfx_simulator
}

def main(build_target_name):
    if not is_docker_image_built():
        build_docker_image()

    BUILD_TARGETS[build_target_name]()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="STM32 Builder",
        description="Builds STM32 components inside the dev container"
    )

    parser.add_argument(
        "build_target_name",
        help=f"""
            Name of the target to build.
            Available targets: {list(BUILD_TARGETS.keys())}
        """
    )
    args = parser.parse_args()

    main(args.build_target_name)
