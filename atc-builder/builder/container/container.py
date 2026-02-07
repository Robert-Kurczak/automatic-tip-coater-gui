"""
Definition of a development container
"""

import sys
import os
import subprocess
from pathlib import Path

from builder.config import environment_paths
from builder.utils.logger import Logger

class Container:
    """
    Dev container containing build dependencies,
    allowing to execute commands inside of it
    """

    def __init__(self, logger: Logger, container_name: str) -> None:
        self.logger = logger
        self.container_name = container_name

        if not self._is_docker_image_built():
            self.build_docker_image()

    def run_container_command(self, command: str, work_directory = Path("/tmp")) -> None:
        """
        Run given command in the dev container

        :param command: Command to be executed
        :type command: str

        :param work_directory:
        Container's directore from where command will be executed
        :type work_directory: Path
        """

        subprocess.run(
            [
                "docker", "run", "--rm", "-it",
                "-u", f"{os.getuid()}:{os.getgid()}",
                "--workdir", work_directory,
                "--volume",
                f"{environment_paths.REPOSITORY_ROOT_PATH}"
                + ":"
                + f"{environment_paths.REPOSITORY_ROOT_PATH}"
                + ":Z",
                self.container_name,
                *command.split()
            ],
            check=True
        )

    def _is_docker_image_built(self) -> bool:
        """
        Checks whether dev image is present in the docker registry
        """

        result = subprocess.run(
            ["docker", "images", "-q", self.container_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
            check=False
        )
        return result.stdout != ""

    def build_docker_image(self):
        """
        Build docker image from dockerfile
        """
        self.logger.log_info("=== Building docker image ===")

        try:
            subprocess.run(
                [
                    "docker", "build",
                    "--tag", self.container_name,
                    "--file", environment_paths.BUILDER_DOCKERFILE_PATH,
                    "."
                ],
                check=True
            )
        except subprocess.CalledProcessError:
            self.logger.log_error("=== Build failed ===")
            sys.exit(1)

        self.logger.log_success("=== Build succeed ===")

