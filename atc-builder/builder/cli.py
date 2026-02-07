#!/usr/bin/env python3
"""
Builder CLI entry point
"""

from builder.container.container import Container
from builder.utils.logger import Logger

def main():
    """
    Entry point
    """

    logger = Logger()
    container = Container(logger, "atc-builder")

    print("Main from cli.py finished")


if __name__ == "__main__":
    main()
