cmake_minimum_required(VERSION 3.10)

project(KingdomEditor)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../KingdomEngine/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/spdlog/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/ImGui/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLEW/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/GLM/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/SDL2/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/stb/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ThirdParty/rapidjson/include"
)

add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
    -D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE KingdomEngine ${CMAKE_SOURCE_DIR}/ThirdParty/SDL2/lib/SDL2main.lib)

if(WIN32)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_SOURCE_DIR}/../bin
    )

    #Copy SDL.dll
    add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/ThirdParty/SDL2/lib/SDL2.dll
        ${CMAKE_CURRENT_SOURCE_DIR}/../bin
    )
endif()
