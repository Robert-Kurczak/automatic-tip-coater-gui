from pathlib import Path

# === Base ===
DEV_DIRECTORY_PATH = Path(__file__).parent
REPOSITORY_ROOT_PATH = DEV_DIRECTORY_PATH.parent.parent
DOCKERFILES_DIRECTORY_PATH = DEV_DIRECTORY_PATH.joinpath("docker")
# ===

# === Files ===
TOUCHGFX_SIMULATOR_PATH = REPOSITORY_ROOT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/build/bin/simulator.out"
)
# ===

# === Dockerfiles ===
STM32_BUILDER_IMAGE_NAME = "atc-stm32-builder"
STM32_BUILDER_DOCKERFILE_PATH = DOCKERFILES_DIRECTORY_PATH.joinpath(
    f"{STM32_BUILDER_IMAGE_NAME}.dockerfile"
)
# ===

# === Docker volumes ===
REPOSITORY_ROOT_MOUNT_PATH = Path("/atc")

MOUNTED_TOUCHGFX_SIMULATOR_MAKEFILE_PATH = REPOSITORY_ROOT_MOUNT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
)
# ===
