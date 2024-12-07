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
            std::string scriptFile =
R"DELIMITER(workspace "PROJECT_NAME"
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
		"KEINCLUDE",
		"THIRDPARTYspdlog/include",
        "THIRDPARTYImGui/include",
        "THIRDPARTYGLEW/include",
        "THIRDPARTYGLM/include",
        "THIRDPARTYSDL2/include",
        "THIRDPARTYstb/include",
        "THIRDPARTYrapidjson/include"
	}

	links
	{
		"EXEDIR/KingdomEngine.lib",
		"THIRDPARTYSDL2/lib/SDL2.lib",
        "THIRDPARTYSDL2/lib/SDL2main.lib",
        "THIRDPARTYGLEW/lib/glew32s.lib",
        "EXEDIR/DearImGui.lib"
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
            std::string exeDir = ReplaceSlash(KE::Core::EXE_DIR);

            //replace words
            scriptFile = ReplaceTextWord(scriptFile, "PROJECT_NAME", projectName);
            scriptFile = ReplaceTextWord(scriptFile, "KEINCLUDE", keIncludeDir);
            scriptFile = ReplaceTextWord(scriptFile, "EXEDIR", exeDir);
            scriptFile = ReplaceTextWord(scriptFile, "THIRDPARTY", thirdpartyDir);

            return scriptFile;
        }

        static std::string GenerateProjectCppFile(std::string projectName)
        {
            projectName.erase(std::remove(projectName.begin(), projectName.end(), ' '), projectName.end());

            std::string cppFile =
R"DELIMITER(#include <KingdomEngine/KingdomEngine.h>

using namespace KE;

class PROJECT_NAME : public Game
{
public:
    void OnReady() override
    {

    }

    void OnUpdate() override
    {

    }

    void OnEvent(Event e) override
    {

    }

};

extern "C" __declspec(dllexport) Game* GameExport()
{
    return new PROJECT_NAME();
}
)DELIMITER";

            cppFile = ReplaceTextWord(cppFile, "PROJECT_NAME", projectName);

            return cppFile;
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
