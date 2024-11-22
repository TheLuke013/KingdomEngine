cmake_minimum_required(VERSION 3.10)

project(KingdomEngine)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLAD/src/glad.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/stb/src/stb_image.cpp"
)

include_directories(
    include
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../KingdomEngine/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/spdlog/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/ImGui/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLAD/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLM/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLFW/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/stb/include"
)

add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
    -D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
    -DGLM_ENABLE_EXPERIMENTAL
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if(WIN32)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
    target_link_libraries(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/ThirdParty/GLFW/lib/glfw3.lib
        DearImGui
        opengl32
    )
endif()