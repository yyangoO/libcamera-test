cmake_minimum_required(VERSION 3.10)

project(libcamera_tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE "Debug")

include_directories(/usr/local/include/libcamera/)

add_executable(libcamera_tests src/main.cpp)

target_link_libraries(libcamera_tests libcamera.so libcamera-base.so)