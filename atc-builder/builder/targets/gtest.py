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
    gcovr_html_file: Path

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

    def _generate_gcovr_html_report(self):
        "Generate gcovr report in html format"

        self.logger.log_info("=== Generating gcovr report ===")

        self.paths.gcovr_html_file.parent.mkdir(parents=True, exist_ok=True)

        gcovr_html_command = "gcovr -r ."
        gcovr_html_command += f" --object-directory {self.paths.build_directory}"
        gcovr_html_command += " --html --html-details"
        gcovr_html_command += " --filter '.*application/.*'"
        gcovr_html_command += " --verbose"
        gcovr_html_command += f" -o {self.paths.gcovr_html_file}"

        try:
            self.container.run_container_command(gcovr_html_command)
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Gcovr report failed ===")
            sys.exit(1)

        self.logger.log_success("=== Generated gcovr report ===")

    def build(self, clean_build: bool, quality_check: bool):
        super().build(clean_build, quality_check)

        self.logger.log_info("=== Building GTest ===")

        clean_command = f"rm -rf {self.paths.build_directory}"
        clean_command = f"rm -rf {self.paths.gcovr_html_file.parent}"

        build_command = f"cmake {self.paths.cmake} -B {self.paths.build_directory}"

        compile_commands = self.paths.build_directory.joinpath("compile_commands.json")
        move_compile_commands_command = \
            f"mv -f {compile_commands} {self.paths.cmake.parent}"

        try:
            if clean_build:
                self.container.run_container_command(clean_command)

            self.container.run_container_command(build_command)
            self.container.run_container_command(
                "make",
                work_directory=self.paths.build_directory
            )

            if clean_build:
                self.container.run_container_command(move_compile_commands_command)

            if quality_check:
                self.run()
                self._generate_gcovr_html_report()

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