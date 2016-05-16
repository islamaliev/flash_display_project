cmake_minimum_required(VERSION 2.8.4)
project(offscreen_render)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${flash_display_INCLUDE_DIRS})

function(add_offscreen_render target)
    file(GLOB ${target}_SOURCE_FILES ${SOURCE_DIR}/${target}/*.cpp ${SOURCE_DIR}/*.cpp)
    add_executable(${target} ${${target}_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${target} ${DISPLAY_LIB_OFFSCREEN_TARGET_NAME})
endfunction()

add_offscreen_render(offscreen_render)
