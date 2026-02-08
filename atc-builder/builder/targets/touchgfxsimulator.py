"Touch GFX Simulator build target"

import subprocess
import sys

from dataclasses import dataclass
from pathlib import Path
from tempfile import NamedTemporaryFile

from ..container.container import Container
from ..utils.logger import Logger
from .target import Target

@dataclass
class TouchGfxSimulatorPaths:
    "Touch GFX simulator related paths"

    clang_tidy_config: Path
    clang_tidy_report: Path
    touchgfx_simulator_makefile: Path
    compile_commands: Path
    touchgfx_binary: Path
    application_directory: Path

class TouchGfxSimulatorTarget(Target):
    "Build target for Touch GFX Simulator"

    def __init__(
            self,
            logger: Logger,
            container: Container,
            paths: TouchGfxSimulatorPaths
        ) -> None:
        super().__init__(logger, container)
        self.paths = paths

    def _check_quality(self, log_file: Path):
        "Run clang-tidy on build target"

        self.logger.log_info("=== Quality check ===")

        clang_tidy_command = "run-clang-tidy"
        clang_tidy_command += " -j16"
        clang_tidy_command += " -use-color True"
        clang_tidy_command += " -extra-arg-before=-Wno-unknown-warning-option"
        clang_tidy_command += f" -config-file {self.paths.clang_tidy_config}"
        clang_tidy_command += f" -export-fixes {log_file}"
        clang_tidy_command += f" -p {self.paths.application_directory}"
        clang_tidy_command += f" {self.paths.application_directory}"

        try:
            self.container.run_container_command(clang_tidy_command)
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Quality check failed ===")
            return

        self.logger.log_success("=== Quality check succeed ===")

    def _generate_clang_html_report(self, log_file: Path):
        "Generate clang-tidy raport in html format"

        self.logger.log_info("=== Generating clang report ===")

        clang_html_command = "clang-tidy-html"
        clang_html_command += f" {log_file} -o {self.paths.clang_tidy_report}"

        try:
            self.container.run_container_command(clang_html_command)
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Clang report failed ===")
            sys.exit(1)

        self.logger.log_success("=== Generated clang report ===")

    def build(self, clean_build: bool, quality_check: bool):
        "Build Touch GFX simulator"

        super().build(clean_build, quality_check)

        self.logger.log_info("=== Building TouchGFX Simulator ===")

        try:
            build_command = f"make -f {self.paths.touchgfx_simulator_makefile} -j16"

            if clean_build:
                build_command = f"bear  --output {self.paths.compile_commands} -- " + build_command
                build_command += " clean"

            build_command += " all"

            self.container.run_container_command(build_command)
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Build failed ===")
            sys.exit(1)

        self.logger.log_success("=== Build succeed ===")

        if quality_check:
            with NamedTemporaryFile(
                dir=self.paths.clang_tidy_report.parent
            ) as temp_file:
                self._check_quality(Path(temp_file.name))
                self._generate_clang_html_report(Path(temp_file.name))

    def run(self) -> None:
        "Run Touch GFX Simulator"

        super().run()

        try:
            subprocess.run(
                [self.paths.touchgfx_binary],
                check=True
            )
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Run failed ===")
            sys.exit(1)

        self.logger.log_success("=== Run succeed ===")
