cmake_minimum_required(VERSION 3.10)
project(8085emu)

# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_library(8085 SHARED
    src/8085.cpp
    src/Execute.cpp
    src/Instruction.cpp
    src/Transfer.cpp
)

add_library(terminal SHARED
    src/Terminal.cpp
)

# Corrected:  Apply include directories to the '8085' and 'terminal' targets.
target_include_directories(8085 PUBLIC include)
target_include_directories(terminal PUBLIC include)

# Create directories if they don't exist
file(MAKE_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/lib
)