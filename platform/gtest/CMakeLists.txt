set(PROJECT_NAME HostTests)

cmake_minimum_required(VERSION 3.14)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(
    REPOSITORY_ROOT
    ${CMAKE_CURRENT_LIST_DIR}/../../
    ABSOLUTE
)
set(APPLICATION_DIR ${REPOSITORY_ROOT}/application)

message("REPOSITORY_ROOT: ${REPOSITORY_ROOT}")
message("APPLICATION_DIR: ${APPLICATION_DIR}")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/HEAD.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE DOMAIN_SOURCES CONFIGURE_DEPENDS
    ${APPLICATION_DIR}/*.cpp
)

file(GLOB_RECURSE TESTS_SOURCES CONFIGURE_DEPENDS
    Tests/*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${DOMAIN_SOURCES}
    ${TESTS_SOURCES}
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    DEBUG_BUILD
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -fprofile-arcs -ftest-coverage -fPIC -O0
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE
    -fprofile-arcs -ftest-coverage --coverage
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ../../
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
