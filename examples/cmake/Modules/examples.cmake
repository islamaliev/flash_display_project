function(add_example target)
    set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/${target})
    file(MAKE_DIRECTORY ${BIN_DIR})
    file(GLOB ${target}_SOURCE_FILES ${SOURCE_DIR}/${target}/*.cpp ${SOURCE_DIR}/*.cpp)
    add_executable(${target} ${${target}_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
    target_link_libraries(${target} ${DISPLAY_LIB_TARGET_NAME})

#    copyFile(${target} vs.glsl)
#    copyFile(${target} fs.glsl)
endfunction()

function(copyFile target fileName)
    STRING(REPLACE "." "_" FILE_VAR ${fileName})
    add_custom_target(${target}_copy_${FILE_VAR} ${CMAKE_COMMAND} -E copy
            ${SOURCE_DIR}/${target}/${fileName} ${BIN_DIR})

    add_dependencies(${target} ${target}_copy_${FILE_VAR})
endfunction()