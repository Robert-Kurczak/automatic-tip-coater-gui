"""
Definition of a development container
"""

import os
import shlex
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

from builder.utils.logger import Logger


@dataclass
class ContainerPaths:
    "Dev container related paths"

    repository_root: Path
    dockerfile: Path


class Container:
    """
    Dev container containing build dependencies,
    allowing to execute commands inside of it
    """

    @staticmethod
    def is_docker_available() -> bool:
        """
        Checks whether docker is available on the machine
        """

        return shutil.which("docker") is not None

    def is_docker_image_built(self) -> bool:
        """
        Checks whether dev image is present in the docker registry
        """

        result = subprocess.run(
            ["sudo", "docker", "images", "-q", self.container_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
            check=False,
        )
        return result.stdout != ""

    def __init__(
        self, logger: Logger, paths: ContainerPaths, container_name: str
    ) -> None:
        self.logger = logger
        self.paths = paths
        self.container_name = container_name

    def run_container_command(
        self, command: str, work_directory=Path("/tmp")
    ) -> None:
        """
        Run given command in the dev container

        :param command: Command to be executed
        :type command: str

        :param work_directory:
        Container's directore from where command will be executed
        :type work_directory: Path
        """

        if not self.is_docker_available():
            self.logger.log_error("Docker dependency is missing")
            return

        if not self.is_docker_image_built():
            self.build_docker_image()

        subprocess.run(
            [
                "sudo",
                "docker",
                "run",
                "--rm",
                "-it",
                "-u",
                f"{os.getuid()}:{os.getgid()}",
                "--workdir",
                work_directory,
                "--volume",
                f"{self.paths.repository_root}"
                + ":"
                + f"{self.paths.repository_root}"
                + ":Z",
                self.container_name,
                *shlex.split(command),
            ],
            check=True,
        )

    def build_docker_image(self):
        """
        Build docker image from dockerfile
        """
        self.logger.log_info("=== Building docker image ===")

        try:
            subprocess.run(
                [
                    "sudo",
                    "docker",
                    "build",
                    "--tag",
                    self.container_name,
                    "--file",
                    self.paths.dockerfile,
                    ".",
                ],
                check=True,
            )
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Build failed ===")
            sys.exit(1)

        self.logger.log_success("=== Build succeed ===")
