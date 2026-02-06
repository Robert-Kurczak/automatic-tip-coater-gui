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
MOUNTED_REPOSITORY_ROOT_PATH = REPOSITORY_ROOT_PATH

MOUNTED_APPLICATION_PATH = REPOSITORY_ROOT_PATH.joinpath("application")

MOUNTED_TOUCHGFX_SIMULATOR_MAKEFILE_PATH = MOUNTED_REPOSITORY_ROOT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
)

MOUNTED_COMPILE_COMMANDS_PATH = MOUNTED_APPLICATION_PATH.joinpath("compile_commands.json")

MOUNTED_CLANG_TIDY_CONFIG_PATH = MOUNTED_REPOSITORY_ROOT_PATH.joinpath(".clang-tidy")

MOUNTED_QUALITY_REPORT_FILE_PATH = MOUNTED_APPLICATION_PATH.joinpath("clang-tidy-report.html")

MOUNTED_HOST_CMAKE_PATH = MOUNTED_REPOSITORY_ROOT_PATH.joinpath("platform/host/CMakeLists.txt")

MOUNTED_HOST_BUILD_DIRECTORY_PATH = MOUNTED_REPOSITORY_ROOT_PATH.joinpath("platform/host/build")
# ===
