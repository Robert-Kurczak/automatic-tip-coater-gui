"""
Definition of a build target
"""

from abc import abstractmethod
from builder.container.container import Container

class Target:
    """
    Target with the capability of being build and run
    """

    def __init__(self, container: Container, name: str) -> None:
        self.container = container
        self.name = name

    @abstractmethod
    def build(self) -> None:
        "Build target in container"

    @abstractmethod
    def run(self) -> None:
        "Run target"
