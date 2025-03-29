cmake_minimum_required(VERSION 3.30)

project(8085emu)

set(CMAKE_CXX_STANDARD 20)

add_executable(8085emu src/main.cpp)

target_include_directories(8085emu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB SOURCES
    "main.cpp"
    "src/*.cpp"
)




