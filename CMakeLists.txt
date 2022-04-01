cmake_minimum_required(VERSION 3.10)

project(libcamera_test VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE "Debug")

find_package(libcamera REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})

add_executable(libcamera_test src/main.cpp)

target_link_libraries(libcamera_test ${OpenCV_LIBS})