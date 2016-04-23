cmake_minimum_required(VERSION 2.8.4)
project(tests)

enable_testing()

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        CACHE INTERNAL "Path to dependencies folder")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(gmock)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/*.cpp)
add_gmock_test(${DISPLAY_LIB_TARGET_NAME}_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(${DISPLAY_LIB_TARGET_NAME}_tests ${DISPLAY_LIB_TARGET_NAME})

