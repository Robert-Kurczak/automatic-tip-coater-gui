#!/usr/bin/env python3
"""
Builder CLI entry point
"""

import argparse
import sys
from enum import StrEnum
from dataclasses import dataclass

from builder.container.container import Container
from builder.utils.logger import Logger
from builder.targets.target import Target

LOGGER = Logger()
CONTAINER = Container(LOGGER, "atc-builder")

BUILD_TARGETS: dict[str, Target] = {}

class BuilderMode(StrEnum):
    "Mode defining what should be done with the target"
    BUILD = "build"
    RUN = "run"
    BUILD_AND_RUN = "build-and-run"

@dataclass
class Args:
    "Command line arguments"
    clean_build: bool
    quality_check: bool
    build_target: Target
    builder_mode: BuilderMode

def parse_arguments() -> Args :
    "Parses user command line arguments"

    parser = argparse.ArgumentParser(
        prog="Builder",
        description="Builds project targets inside the dev containers"
    )

    parser.add_argument(
        "builder_mode",
        type=BuilderMode,
        choices=list(BuilderMode),
        help=f"""
            What should be done with the target.
            Available modes: {[x.value for x in BuilderMode]}
        """
    )

    parser.add_argument(
        "target_name",
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
    build_target = BUILD_TARGETS.get(args.target_name)

    if build_target is None:
        print(f"Target '{args.target_name}' not found")
        print(f"Available targets: {list(BUILD_TARGETS.keys())}")
        sys.exit(1)

    return Args(
        clean_build=args.clean_build,
        quality_check=args.quality_check,
        build_target=args.build_target,
        builder_mode=args.builder_mode
    )

def main():
    """
    Entry point
    """

    args = parse_arguments()

    match args.builder_mode:
        case BuilderMode.BUILD:
            args.build_target.build()
        case BuilderMode.RUN:
            args.build_target.run()
        case BuilderMode.BUILD_AND_RUN:
            args.build_target.build()
            args.build_target.run()


if __name__ == "__main__":
    main()
