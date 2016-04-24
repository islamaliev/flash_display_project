set (glfw_DIR ${DEPENDENCIES_DIR}/glfw)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Don't build example")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Don't build tests")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Don't build docs")
add_subdirectory(${glfw_DIR} ${CMAKE_BINARY_DIR}/glfw)
set_target_properties(glfw PROPERTIES COMPILE_FLAGS " -w")

# find OpenGL
find_package(OpenGL REQUIRED)
set(ADDITIONAL_LIBRARIES ${OPENGL_LIBRARIES})

include_directories(${glfw_DIR}/include)

function(link_glfw target)
    target_link_libraries(${target} glfw glew ${ADDITIONAL_LIBRARIES})
endfunction()