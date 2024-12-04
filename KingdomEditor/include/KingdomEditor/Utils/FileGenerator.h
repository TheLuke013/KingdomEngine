#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <string>
#include <algorithm>

namespace Editor
{
    class FileGenerator
    {
    public:
        static std::string GenerateCMakeFile(std::string projectName)
        {
            projectName.erase(std::remove(projectName.begin(), projectName.end(), ' '), projectName.end());
            std::string cmakeFile = R"DELIMITER(
cmake_minimum_required(VERSION 3.10)

project(PROJECT_NAME)

file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/KingdomEngine/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/spdlog/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/ImGui/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/GLEW/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/GLM/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/SDL2/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/stb/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ThirdParty/rapidjson/include"
)

add_definitions(
    -D_CRT_SECURE_NO_WARNINGS
    -D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
    -D_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

if(WIN32)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
    target_link_libraries(${PROJECT_NAME}
        KingdomEngine/bin/KingdomEngine.lib
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_CURRENT_SOURCE_DIR}/bin
    )
endif()
)DELIMITER";

            size_t pos = cmakeFile.find("PROJECT_NAME");
            if (pos != std::string::npos)
            {
                cmakeFile.replace(pos, 12, projectName);
            }

            return cmakeFile;
        }
    };
}

#endif