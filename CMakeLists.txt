cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME libcamera_tests)

project(${PROJECT_NAME} VERSION 1.0)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
        message(STATUS "No previous build - default to Release build")
    endif()
endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Wno-unused-parameter -faligned-new -Werror -Wfatal-errors)
add_definitions(-D_FILE_OFFSET_BITS=64)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wno-psabi)
endif()

option(BUILD_SHARED_LIBS "[build using shared libraries. ]" ON)

set(CPACK_GENERATOR "TXZ")
set(CPACK_PACKAGE_FILE_NAME "libcamrea_tests-build")
set(CPACK_SOURCE_GENERATOR "TXZ")
set(CPACK_INSTALL_SCRIPTS ${CMAKE_SOURCE_DIR}/package.cmake)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "libcamrea_tests-src")
set(CPACK_SOURCE_IGNORE_FILES "/\.git*;/build;")
include(CPack)

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBCAMERA REQUIRED libcamera)
message(STATUS "libcamera library found:")
message(STATUS "    version: ${LIBCAMERA_VERSION}")
message(STATUS "    libraries: ${LIBCAMERA_LINK_LIBRARIES}")
message(STATUS "    include path: ${LIBCAMERA_INCLUDE_DIRS}")
include_directories(include ${LIBCAMERA_INCLUDE_DIRS})

pkg_check_modules(LIBEVENT REQUIRED libevent)
set(LIBEVENT_PTHREADS_LINK_LIBRARIES libevent_pthreads.so)
message(STATUS "libevent library found:")
message(STATUS "    version: ${LIBEVENT_VERSION}")
message(STATUS "    libraries: ${LIBEVENT_LINK_LIBRARIES}")
message(STATUS "    libraries: ${LIBEVENT_PTHREADS_LINK_LIBRARIES}")

include(GNUInstallDirs)

set(SOURCES
    src/main.cpp
    src/eventloop.cpp
)
set(HEADERS
    src/utils.h
    src/eventloop.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" IMPORT_PREFIX "")
target_link_libraries(${PROJECT_NAME} ${LIBCAMERA_LINK_LIBRARIES} 
                                      ${LIBEVENT_LINK_LIBRARIES} 
                                      ${LIBEVENT_PTHREADS_LINK_LIBRARIES})