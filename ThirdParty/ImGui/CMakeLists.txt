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