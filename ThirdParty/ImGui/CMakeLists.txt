cmake_minimum_required(VERSION 3.10)

project(DearImGui)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ImGui"
    "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include/SDL"
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_SOURCE_DIR}/../../bin
    )
endif()
