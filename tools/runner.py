#!/usr/bin/env python3

import sys
import subprocess
import argparse
from dev import common
from dev import paths

def run_touchgfx_simulator():
    try:
        subprocess.run(
            [paths.TOUCHGFX_SIMULATOR_PATH],
            check=True
        )
    except subprocess.CalledProcessError:
        common.log_error("=== Run failed ===")
        sys.exit(1)

    common.log_success("=== Run succeed ===")


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
