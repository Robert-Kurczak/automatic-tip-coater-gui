from pathlib import Path
from builder.targets.touchgfxsimulator import TouchGfxSimulatorPaths
from builder.container.container import ContainerPaths

# === Base ===
BUILDER_DIRECTORY_PATH = Path(__file__).parent.parent.parent
REPOSITORY_ROOT_PATH = BUILDER_DIRECTORY_PATH.parent
APPLICATION_PATH = REPOSITORY_ROOT_PATH.joinpath("application")
# ===

TOUCHGFX_SIMULATOR_PATHS = TouchGfxSimulatorPaths(
    clang_tidy_config = REPOSITORY_ROOT_PATH.joinpath(".clang-tidy"),
    clang_tidy_report = APPLICATION_PATH.joinpath("clang-tidy-report.html"),
    touchgfx_simulator_makefile = REPOSITORY_ROOT_PATH.joinpath(
        "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
    ),
    compile_commands = APPLICATION_PATH.joinpath("compile_commands.json"),
    touchgfx_binary = REPOSITORY_ROOT_PATH.joinpath(
        "platform/nucleo-u5a5zj/TouchGFX/build/bin/simulator.out"
    ),
    application_directory = APPLICATION_PATH
)

CONTAINER_PATHS = ContainerPaths(
    repository_root = REPOSITORY_ROOT_PATH,
    dockerfile = BUILDER_DIRECTORY_PATH.joinpath(
        "container/atc-builder.dockerfile"
    )
)




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
