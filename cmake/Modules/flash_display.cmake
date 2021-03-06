set(DISPLAY_LIB flash_display)
set(${DISPLAY_LIB}_SOURCE_DIR ${CMAKE_SOURCE_DIR}/${DISPLAY_LIB})

add_subdirectory(${${DISPLAY_LIB}_SOURCE_DIR})

set(DISPLAY_LIB_TARGET_NAME ${${DISPLAY_LIB}_TARGET_NAME})
set(DISPLAY_LIB_OFFSCREEN_TARGET_NAME ${${DISPLAY_LIB}_OFFSCREEN_TARGET_NAME})

include_directories(${${DISPLAY_LIB}_INCLUDE_DIRS})