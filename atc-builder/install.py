#!/bin/env python3

import subprocess
from pathlib import Path

CURRENT_DIRECTORY = Path(__file__).parent

if __name__ == "__main__":
    subprocess.run(
        ["pip", "install", "-e", CURRENT_DIRECTORY],
        check=False
    )
