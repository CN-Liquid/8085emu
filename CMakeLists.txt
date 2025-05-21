cmake_minimum_required(VERSION 3.16)
project(8085emu)

# Option to choose version
set(PROJECT_VERSION "" CACHE STRING "Choose version: debug or release")

# Load version-specific config
if(PROJECT_VERSION STREQUAL "debug")
    include(cmake/debug.cmake)
elseif(PROJECT_VERSION STREQUAL "release")
    include(cmake/release.cmake)
else()
    message(FATAL_ERROR "Please set -DPROJECT_VERSION=debug or release")
endif()
