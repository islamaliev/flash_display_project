cmake_minimum_required(VERSION 2.8.4)
project(tests)

enable_testing()

set(MATH_LIB flash_math)

set(${MATH_LIB}_SOURCE_DIR ../${MATH_LIB})
add_subdirectory(${${MATH_LIB}_SOURCE_DIR} ${CMAKE_BINARY_DIR}/${MATH_LIB})

set(MATH_LIB_TARGET_NAME ${${MATH_LIB}_TARGET_NAME})

include_directories(
        ${${MATH_LIB}_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        CACHE INTERNAL "Path to dependencies folder")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(gmock)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/*.cpp)
add_gmock_test(${MATH_LIB_TARGET_NAME}_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(${MATH_LIB_TARGET_NAME}_tests ${MATH_LIB_TARGET_NAME})

