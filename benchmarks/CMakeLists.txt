cmake_minimum_required(VERSION 2.8.4)
project(benchmarks)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCE_FILES "${SOURCE_DIR}/benchmarks.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

