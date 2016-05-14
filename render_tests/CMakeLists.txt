cmake_minimum_required(VERSION 2.8.4)
project(render_tests)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${flash_display_INCLUDE_DIRS})

include(render_tests)

add_render_test(main_render_test)
