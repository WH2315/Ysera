cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    Ysera
    LANGUAGES CXX C
)

include(cmake/vulkan.cmake)
include(cmake/3rdlibs.cmake)

add_subdirectory(renderer)

option(BUILD_SANDBOX "build sandbox" ON)
if (BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()