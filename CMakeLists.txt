cmake_minimum_required(VERSION 3.10)
project(mosco VERSION 0.1 LANGUAGES C)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB SOURCES src/*.c)

set(LICENSE "GPLv3 license")

add_executable(mosco ${SOURCES})


