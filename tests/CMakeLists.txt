cmake_minimum_required(VERSION 2.8.4)
project(tests)

enable_testing()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TEST_SOURCE_FILES 
    "${SOURCE_DIR}/Color_Test.cpp"
    "${SOURCE_DIR}/Component_SortingTest.cpp"
    "${SOURCE_DIR}/Component_Test.cpp"
    "${SOURCE_DIR}/DisplayObject_DepthTest.cpp"
    "${SOURCE_DIR}/DisplayObject_GetTransformTest.cpp"
    "${SOURCE_DIR}/DisplayObject_OrderIndexTest.cpp"
    "${SOURCE_DIR}/DisplayObject_Test.cpp"
    "${SOURCE_DIR}/DisplayObject_TreeSizeTest.cpp"
    "${SOURCE_DIR}/DisplayObject_VisibilityTest.cpp"
    "${SOURCE_DIR}/DisplayObjectContainer_Test.cpp"
    "${SOURCE_DIR}/Image_Test.cpp"
    "${SOURCE_DIR}/matrix_asserts.cpp"
    "${SOURCE_DIR}/matrix_asserts.h"
    "${SOURCE_DIR}/Rectangle_Test.cpp"
    "${SOURCE_DIR}/RenderBufferOrganizer_Test.cpp"
    "${SOURCE_DIR}/StackAllocator_Test.cpp"
    "${SOURCE_DIR}/Stage_Test.cpp"
    "${SOURCE_DIR}/StageBasedTest.h"
    "${SOURCE_DIR}/tests.cpp")

get_property(gtest_INCLUDE_DIRECTORIES TARGET CONAN_PKG::gtest PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${gtest_INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS} CONAN_PKG::gtest)

