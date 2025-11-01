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

def log_info(message):
    bold_font_start = "\x1b[1;39;49m"
    bold_font_stop = "\x1b[0m"

    print(bold_font_start + message + bold_font_stop)


def log_error(message):
    red_color_start = "\x1b[1;31;49m"
    red_color_stop = "\x1b[0m"

    print(red_color_start + message + red_color_stop)

def log_success(message):
    green_color_start = "\x1b[1;32;49m"
    green_color_end = "\x1b[0m"

    print(green_color_start + message + green_color_end)

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
    log_info("=== Building docker image ===")

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
        log_error("=== Build failed ===")
        sys.exit(1)

    log_success("=== Build succeed ===")

def build_touchgfx_simulator(clean):
    try:
        build_command = f"make -f {SIMULATOR_MAKEFILE_MOUNT_PATH} -j16"
        if clean:
            build_command += " clean"
        build_command += " all"

        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{REPOSITORY_ROOT_DIR}:{REPOSITORY_ROOT_MOUNT_PATH}:Z",
                "--env", f"ADDITIONAL_SOURCES_DIR={APPLICATION_MOUNT_PATH}",
                "--env", f"ADDITIONAL_INCLUDE_DIR={REPOSITORY_ROOT_MOUNT_PATH}",
                STM32_BUILDER_IMAGE_NAME,
                *build_command.split()
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        log_error("=== Build failed ===")
        sys.exit(1)

    log_success("=== Build succeed ===")


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
