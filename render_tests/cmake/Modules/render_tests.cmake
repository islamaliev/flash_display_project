function(add_render_test target)
#    set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/${target})
#    file(MAKE_DIRECTORY ${BIN_DIR})
    file(GLOB ${target}_SOURCE_FILES ${SOURCE_DIR}/${target}/*.cpp ${SOURCE_DIR}/*.cpp)
    add_executable(${target} ${${target}_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
#    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
    target_link_libraries(${target} ${DISPLAY_LIB_OFFSCREEN_TARGET_NAME})
endfunction()
