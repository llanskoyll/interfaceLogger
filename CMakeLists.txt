cmake_minimum_required(VERSION 3.0)

project(portLogger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILE})

target_include_directories(${PROJECT_NAME} PUBLIC include)