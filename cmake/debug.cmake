# Set the output directory for libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_executable(8085emu
    src/main.cpp
    src/8085.cpp
    src/Execute.cpp
    src/Instruction.cpp
    src/Transfer.cpp
    src/Terminal.cpp
)


# Corrected:  Apply include directories to the '8085' and 'terminal' targets.
target_include_directories(8085emu PUBLIC include)

