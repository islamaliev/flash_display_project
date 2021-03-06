cmake_minimum_required(VERSION 2.8.4)
project(flash_display_project)

set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
#set (CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

if(MSVC)
set (CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} /EHsc /D_USE_MATH_DEFINES")
else()
set (CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++14 -Wall -Wno-missing-braces")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

set (CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include(flash_display)

add_subdirectory(tests)

add_subdirectory(render_tests)

add_subdirectory(examples)

add_subdirectory(benchmarks)

