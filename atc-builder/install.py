#!/bin/env python3

import subprocess
from pathlib import Path

from builder.utils.logger import Logger

CURRENT_DIRECTORY = Path(__file__).parent

HOST_DEPENDENCIES = {
    "docker": "For building targets in dev container",
    "SDL2_image-devel": "For running device UI on dev host machine",
}


def print_dependencies(logger: Logger):
    """
    Prints dependencies required on host machine
    """

    logger.log_info("=== Required host dependencies: ===")

    for dep in HOST_DEPENDENCIES:
        logger.log_info(f"\t* {dep}\n", end="")

    logger.log_info("")


def main():
    """
    Entry point
    """

    logger = Logger()

    print_dependencies(logger)

    subprocess.run(
        ["pip", "install", "-e", CURRENT_DIRECTORY], check=False
    )


if __name__ == "__main__":
    main()
