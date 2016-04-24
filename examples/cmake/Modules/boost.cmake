set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})

function(link_boost target)
    target_link_libraries(${target} ${Boost_LIBRARIES})
endfunction()