cmake_minimum_required(VERSION 2.8.4)
project(image_dif)

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

#set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

find_package(PNG REQUIRED)

#message("image_dif png version: " ${PNG_VERSION_STRING})
message("image_dif include dir: " ${PNG_INCLUDE_DIRS})
#message("image_dif include dir: " ${PNG_INCLUDE_DIR})

include_directories("/usr/local/include")

foreach(include_dir ${PNG_INCLUDE_DIRS})
    message("in loop: " ${include_dir})
    include_directories(${include_dir})
endforeach(include_dir)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#include_directories(${flash_display_INCLUDE_DIRS})

#include(offscreen_render)

add_executable(image_dif ${SOURCE_DIR}/image_dif.c)
target_link_libraries(image_dif ${PNG_LIBRARIES})
set_target_properties(image_dif PROPERTIES LINKER_LANGUAGE C)
