cmake_minimum_required(VERSION 3.0)

project(interfaceLogger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILE})

find_package(PcapPlusPlus REQUIRED)
find_package(Boost REQUIRED)

target_link_libraries(${PROJECT_NAME} PcapPlusPlus::Pcap++)
target_link_libraries(${PROJECT_NAME} ${Boost})

target_include_directories(${PROJECT_NAME} PUBLIC include)