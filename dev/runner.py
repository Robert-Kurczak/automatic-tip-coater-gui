#!/usr/bin/env python3

import sys
import subprocess
from pathlib import Path
import argparse

REPOSITORY_ROOT_DIR = Path(__file__).parent.parent

TOUCHGFX_DIR_PATH = REPOSITORY_ROOT_DIR.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX"
)

TOUCHGFX_SIMULATOR_PATH = TOUCHGFX_DIR_PATH.joinpath(
    "build/bin/simulator.out"
)

def log_info(message):
    bold_font_start = "\x1b[1;39;49m"
    bold_font_stop = "\x1b[0m"

    print(bold_font_start + message + bold_font_stop)


def log_error(message):
    red_color_start = "\x1b[1;31;49m"
    red_color_stop = "\x1b[0m"

    print(red_color_start + message + red_color_stop)

def log_success(message):
    green_color_start = "\x1b[1;32;49m"
    green_color_end = "\x1b[0m"

    print(green_color_start + message + green_color_end)


def run_touchgfx_simulator():
    try:
        subprocess.run(
            [TOUCHGFX_SIMULATOR_PATH],
            check=True
        )
    except subprocess.CalledProcessError:
        log_error("=== Run failed ===")
        sys.exit(1)

    log_success("=== Run succeed ===")


RUN_TARGETS = {
    "touchgfx-simulator": run_touchgfx_simulator
}

def main(run_target_function):
    run_target_function()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="ATC Runner",
        description="Runs ATC targets on host machine"
    )

    parser.add_argument(
        "run_target_name",
        type=str,
        help=f"""
            Name of the target to run.
            Available targets: {list(RUN_TARGETS.keys())}
        """
    )

    args = parser.parse_args()

    choosen_target = args.run_target_name
    run_target = RUN_TARGETS.get(choosen_target)

    if run_target is None:
        print(f"Target '{choosen_target}' not found")
        print(f"Available targets: {list(RUN_TARGETS.keys())}")
        sys.exit(1)

    main(run_target)
