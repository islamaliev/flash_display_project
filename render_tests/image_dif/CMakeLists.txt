cmake_minimum_required(VERSION 2.8.4)
project(image_dif)

get_property(libpng_INCLUDE_DIRS TARGET CONAN_PKG::libpng PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${PROJECT_NAME} ${libpng_INCLUDE_DIRS})

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME} "${SOURCE_DIR}/image_diff.c")
target_link_libraries(${PROJECT_NAME} CONAN_PKG::libpng)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
