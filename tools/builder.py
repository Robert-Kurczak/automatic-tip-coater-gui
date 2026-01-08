#!/usr/bin/env python3

import sys
import subprocess
import os
import argparse
from tempfile import NamedTemporaryFile
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

def check_touchgfx_simulator_quality(clang_log_file_path):
    common.log_info("=== Quality check ===")

    clang_tidy_command = "run-clang-tidy"
    clang_tidy_command += " -j16"
    clang_tidy_command += " -use-color True"
    clang_tidy_command += f" -config-file {paths.MOUNTED_CLANG_TIDY_CONFIG_PATH}"
    clang_tidy_command += f" -export-fixes {clang_log_file_path}"
    clang_tidy_command += f" -p {paths.MOUNTED_APPLICATION_PATH}"
    clang_tidy_command += f" {paths.MOUNTED_APPLICATION_PATH}"

    try:
        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{paths.REPOSITORY_ROOT_PATH}:{paths.MOUNTED_REPOSITORY_ROOT_PATH}:Z",
                paths.STM32_BUILDER_IMAGE_NAME,
                *clang_tidy_command.split()
            ],
            check=True
        )

    except subprocess.CalledProcessError:
        common.log_error("=== Quality check failed ===")
        return

    common.log_success("=== Quality check succeed ===")

def generate_clang_html_report(clang_log_file_path):
    common.log_info("=== Generating clang report ===")

    clang_html_command = "clang-tidy-html"
    clang_html_command += f" {clang_log_file_path} -o {paths.MOUNTED_QUALITY_REPORT_FILE_PATH}"

    try:
        subprocess.run(
                [
                    "docker", "run", "--rm", "-it",
                    "-u", f"{os.getuid()}:{os.getgid()}",
                    "--volume", f"{paths.REPOSITORY_ROOT_PATH}:{paths.MOUNTED_REPOSITORY_ROOT_PATH}:Z",
                    paths.STM32_BUILDER_IMAGE_NAME,
                    *clang_html_command.split()
                ],
                check=True
            )

    except subprocess.CalledProcessError:
        common.log_error("=== Clang report failed ===")
        sys.exit(1)

    common.log_success("=== Generated clang report ===")

def build_touchgfx_simulator(clean, quality_check):
    common.log_info("=== Building TouchGFX Simulator ===")

    try:
        build_command = f"make -f {paths.MOUNTED_TOUCHGFX_SIMULATOR_MAKEFILE_PATH} -j16"

        if clean:
            build_command = f"bear  --output {paths.MOUNTED_COMPILE_COMMANDS_PATH} -- " + build_command
            build_command += " clean"

        build_command += " all"

        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--volume", f"{paths.REPOSITORY_ROOT_PATH}:{paths.MOUNTED_REPOSITORY_ROOT_PATH}:Z",
                paths.STM32_BUILDER_IMAGE_NAME,
                *build_command.split()
            ],
            check=True
        )
    except subprocess.CalledProcessError:
        common.log_error("=== Build failed ===")
        sys.exit(1)

    common.log_success("=== Build succeed ===")

    if quality_check:
        with NamedTemporaryFile(
            dir=paths.MOUNTED_QUALITY_REPORT_FILE_PATH.parent
        ) as temp_file:
            check_touchgfx_simulator_quality(temp_file.name)
            generate_clang_html_report(temp_file.name)

BUILD_TARGETS = {
    "touchgfx-simulator": build_touchgfx_simulator
}

def main(build_target_function, clean, quality_check):
    if not is_docker_image_built():
        build_docker_image()

    build_target_function(clean, quality_check)

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

    parser.add_argument(
        "-q", "--quality-check",
        action="store_true",
        help="Check code quality using clang-tidy"
    )

    args = parser.parse_args()

    choosen_target = args.build_target_name
    build_target = BUILD_TARGETS.get(choosen_target)

    if build_target is None:
        print(f"Target '{choosen_target}' not found")
        print(f"Available targets: {list(BUILD_TARGETS.keys())}")
        sys.exit(1)

    main(build_target, args.clean, args.quality_check)
