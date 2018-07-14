cmake_minimum_required(VERSION 2.8.4)
project(flash_display_project)

set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(FLASH_DISPLAY_PATH "" CACHE PATH "Path to flash_display project root")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if(MSVC)
    set (CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} /EHsc /D_USE_MATH_DEFINES")
else()
    set (CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++14 -Wall -Wno-missing-braces")
endif()

if("${FLASH_DISPLAY_PATH}" STREQUAL "")
    list(APPEND LINK_LIBS CONAN_PKG::flash_display)
else()
    set(SUFFIX "")
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(SUFFIX "d")
    endif()
    list(APPEND LINK_LIBS "flash_display${SUFFIX}")
    add_subdirectory(${FLASH_DISPLAY_PATH} ${CMAKE_CURRENT_BINARY_DIR}/flash_display)
    get_property(flash_display_INCLUDE_DIRECTORIES TARGET flash_display PROPERTY INCLUDE_DIRECTORIES)
    include_directories(${flash_display_INCLUDE_DIRECTORIES})
    link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

add_subdirectory(tests)

add_subdirectory(render_tests)

add_subdirectory(examples)

add_subdirectory(benchmarks)
