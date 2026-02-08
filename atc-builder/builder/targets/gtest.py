"GTest build target"

import subprocess
import sys

from dataclasses import dataclass
from pathlib import Path

from ..container.container import Container
from ..utils.logger import Logger

from .target import Target

@dataclass
class GTestPaths:
    "GTest related paths"

    build_directory: Path
    cmake: Path

class GTestTarget(Target):
    "Build target for GTest"

    def __init__(
            self,
            logger: Logger,
            container: Container,
            paths: GTestPaths
        ) -> None:
        super().__init__(logger, container)
        self.paths = paths

    def build(self, clean_build: bool, quality_check: bool):
        super().build(clean_build, quality_check)

        self.logger.log_info("=== Building GTest ===")

        clean_command = f"rm -rf {self.paths.build_directory}"
        build_command = f"cmake {self.paths.cmake} -B {self.paths.build_directory}"

        try:
            if clean_build:
                self.container.run_container_command(clean_command)

            self.container.run_container_command(build_command)
            self.container.run_container_command(
                "make",
                work_directory=self.paths.build_directory
            )

        except subprocess.CalledProcessError:
            self.logger.log_error("=== GTest build failed ===")

    def run(self):
        super().run()

        self.logger.log_info("=== Running GTest ===")

        try:
            self.container.run_container_command(
                "ctest",
                work_directory=self.paths.build_directory
            )
        except subprocess.CalledProcessError:
            self.logger.log_error("=== GTest failed ===")
            sys.exit(1)