cmake_minimum_required(VERSION 2.8.4)
project(examples)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

function(add_example target)
    file(GLOB ${target}_SOURCE_FILES ${SOURCE_DIR}/${target}/*.cpp ${SOURCE_DIR}/*.cpp)
    add_executable(${target} ${${target}_SOURCE_FILES})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${target} ${LINK_LIBS})

#    copyFile(${target} vs.glsl)
#    copyFile(${target} fs.glsl)
endfunction()

function(copyFile target fileName)
    STRING(REPLACE "." "_" FILE_VAR ${fileName})
    add_custom_target(${target}_copy_${FILE_VAR} ${CMAKE_COMMAND} -E copy
            ${SOURCE_DIR}/${target}/${fileName} ${BIN_DIR})

    add_dependencies(${target} ${target}_copy_${FILE_VAR})
endfunction()

add_example(example1)
add_example(example2)
