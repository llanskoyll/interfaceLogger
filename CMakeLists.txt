cmake_minimum_required(VERSION 3.27)

cmake_policy(SET CMP0167 NEW)

project(interfaceLogger)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILE "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories(include)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILE})

find_package(PcapPlusPlus REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem chrono)

if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    message(STATUS "Boost include directories: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost not found")
endif()

if(PcapPlusPlus_FOUND)
    message(STATUS "PcapPlusPlus found: ${PcapPlusPlus_VERSION}")
    message(STATUS "PcapPlusPlus include directories: ${PCAPPLUSPLUS_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "PcapPlusPlus not found")
endif()

target_link_libraries(${PROJECT_NAME} PcapPlusPlus::Pcap++ ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
