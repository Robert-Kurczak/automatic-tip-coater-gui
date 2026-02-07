from pathlib import Path

# === Base ===
BUILDER_DIRECTORY_PATH = Path(__file__).parent.parent
REPOSITORY_ROOT_PATH = BUILDER_DIRECTORY_PATH.parent
# ===

# === Files ===
TOUCHGFX_SIMULATOR_PATH = REPOSITORY_ROOT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/build/bin/simulator.out"
)

BUILDER_DOCKERFILE_PATH = BUILDER_DIRECTORY_PATH.joinpath(
    "container/atc-builder.dockerfile"
)

APPLICATION_PATH = REPOSITORY_ROOT_PATH.joinpath("application")

TOUCHGFX_SIMULATOR_MAKEFILE_PATH = REPOSITORY_ROOT_PATH.joinpath(
    "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
)

COMPILE_COMMANDS_PATH = APPLICATION_PATH.joinpath("compile_commands.json")

CLANG_TIDY_CONFIG_PATH = REPOSITORY_ROOT_PATH.joinpath(".clang-tidy")

QUALITY_REPORT_FILE_PATH = APPLICATION_PATH.joinpath("clang-tidy-report.html")

HOST_CMAKE_PATH = REPOSITORY_ROOT_PATH.joinpath("platform/host/CMakeLists.txt")

HOST_BUILD_DIRECTORY_PATH = REPOSITORY_ROOT_PATH.joinpath("platform/host/build")
# ===
