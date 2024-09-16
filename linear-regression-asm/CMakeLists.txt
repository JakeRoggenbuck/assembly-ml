cmake_minimum_required(VERSION 3.3)
project(linearregressionasm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/debug")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

file(GLOB_RECURSE SOURCES src/*.c src/*.s)

add_executable(regression_test ${SOURCES})
target_include_directories(regression_test PRIVATE src)

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -g -c -m64")
