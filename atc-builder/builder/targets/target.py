"""
Definition of a build target
"""

from abc import abstractmethod
from builder.container.container import Container
from builder.utils.logger import Logger

class Target:
    """
    Target with the capability of being build and run
    """

    def __init__(self, logger: Logger, container: Container) -> None:
        self.logger = logger
        self.container = container

    @abstractmethod
    def build(self, clean_build: bool, quality_check: bool) -> None:
        "Build target in container"

    @abstractmethod
    def run(self) -> None:
        "Run target"
