"File system paths for build targets"

from pathlib import Path
from builder.targets.touchgfxsimulator import TouchGfxSimulatorPaths
from builder.targets.gtest import GTestPaths
from builder.container.container import ContainerPaths

# === Base ===
BUILDER_DIRECTORY_PATH = Path(__file__).parent.parent.parent
REPOSITORY_ROOT_PATH = BUILDER_DIRECTORY_PATH.parent
APPLICATION_PATH = REPOSITORY_ROOT_PATH.joinpath("application")
REPORTS_DIRECTORY_PATH = APPLICATION_PATH.joinpath("Reports")
# ===

CONTAINER_PATHS = ContainerPaths(
    repository_root = REPOSITORY_ROOT_PATH,
    dockerfile = BUILDER_DIRECTORY_PATH.joinpath(
        "builder/container/atc-builder.dockerfile"
    )
)

TOUCHGFX_SIMULATOR_PATHS = TouchGfxSimulatorPaths(
    clang_tidy_config = REPOSITORY_ROOT_PATH.joinpath(".clang-tidy"),
    clang_tidy_report = REPORTS_DIRECTORY_PATH.joinpath("clang-tidy-report.html"),
    touchgfx_simulator_makefile = REPOSITORY_ROOT_PATH.joinpath(
        "platform/nucleo-u5a5zj/TouchGFX/simulator/gcc/Makefile"
    ),
    compile_commands = APPLICATION_PATH.joinpath("compile_commands.json"),
    touchgfx_binary = REPOSITORY_ROOT_PATH.joinpath(
        "platform/nucleo-u5a5zj/TouchGFX/build/bin/simulator.out"
    ),
    application_directory = APPLICATION_PATH
)

GTEST_PATHS = GTestPaths(
    build_directory = REPOSITORY_ROOT_PATH.joinpath("platform/gtest/build"),
    cmake = REPOSITORY_ROOT_PATH.joinpath("platform/gtest/CMakeLists.txt"),
    gcovr_html_file = REPORTS_DIRECTORY_PATH.joinpath("gcovr/gcovr-report.html")
)
