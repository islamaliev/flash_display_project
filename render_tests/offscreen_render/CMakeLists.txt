cmake_minimum_required(VERSION 2.8.4)
project(offscreen_render)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCE_FILES 
    "${SOURCE_DIR}/offscreen_render.cpp"
    "${SOURCE_DIR}/render_fixtures.cpp"
    "${SOURCE_DIR}/render_fixtures.h")

get_property(flash_math_INCLUDE_DIRS TARGET CONAN_PKG::flash_math PROPERTY INTERFACE_INCLUDE_DIRECTORIES)

include_directories(${flash_math_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

