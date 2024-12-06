#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <KingdomEngine/KingdomEngine.h>

#include <string>
#include <algorithm>

namespace Editor
{
    class FileGenerator
    {
    public:
        static std::string GenerateBuildScriptFile(std::string projectName)
        {
            std::string scriptFile = R"DELIMITER(
workspace "PROJECT_NAME"
	architecture "x64"
	configurations
	{
		"Release"
	}

project "PROJECT_NAME"
	kind "SharedLib"
	language "C++"

	targetdir ("build/")
	objdir ("build/obj")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"KEINCLUDEKingdomEngine/include",
		"THIRDPARTYspdlog/include",
		"THIRDPARTYImGui/include",
		"THIRDPARTYGLAD/include",
		"THIRDPARTYGLM/include",
		"THIRDPARTYGLFW/include",
		"THIRDPARTYstb/include"
	}

	links
	{
		"KELIB"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"
)DELIMITER";

            //replace slahses
            std::string thirdpartyDir = ReplaceSlash(KE::Core::THIRDPARTY_DIR);
            std::string keIncludeDir = ReplaceSlash(KE::Core::KE_INCLUDE_DIR);
            std::string keLibFile = ReplaceSlash(KE::Core::KE_LIB_FILE);

            //replace words
            scriptFile = ReplaceTextWord(scriptFile, "PROJECT_NAME", projectName);
            scriptFile = ReplaceTextWord(scriptFile, "KEINCLUDE", keIncludeDir);
            scriptFile = ReplaceTextWord(scriptFile, "KELIB", keLibFile);
            scriptFile = ReplaceTextWord(scriptFile, "THIRDPARTY", thirdpartyDir);

            return scriptFile;
        }

    private:
        static std::string ReplaceSlash(const std::string& slashToReplace)
        {
            std::string slashStr = slashToReplace;
            size_t slashPos = 0;
            while ((slashPos = slashStr.find("\\", slashPos)) != std::string::npos)
            {
                slashStr.replace(slashPos, 1, "/");
                slashPos += 2;
            }

            return slashStr;
        }

        static std::string ReplaceTextWord(const std::string& text, const std::string& fromWord, const std::string& toWord)
        {
            std::string wordStr = text;
            size_t thirdpartyDirPos = 0;
            size_t fromWordLength = fromWord.length();

            while ((thirdpartyDirPos = wordStr.find(fromWord, thirdpartyDirPos)) != std::string::npos)
            {
                wordStr.replace(thirdpartyDirPos, fromWordLength, toWord);
                thirdpartyDirPos += toWord.length();
            }

            return wordStr;
        }

    };
}

#endif
