cmake_minimum_required(VERSION 3.10)

project(DearImGui)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ImGui"
    "${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/include"
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if(WIN32)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin"
    )
endif()