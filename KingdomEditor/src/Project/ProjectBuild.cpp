#include "KingdomEditor/Project/ProjectBuild.h"
#include "KingdomEditor/DialogBox/BuildErrorDialogBox.h"
#include "KingdomEditor/Utils/Globals.h"
#include "KingdomEditor/Utils/FileGenerator.h"

namespace Editor
{
    float ProjectBuild::buildProgress = 0.0f;
    bool ProjectBuild::buildDone = false;
    bool ProjectBuild::buildStarted = false;
    bool ProjectBuild::generatingBuildFiles = false;
    std::atomic<bool> ProjectBuild::filesGenerated = false;
    std::atomic<bool> ProjectBuild::compileDone = false;

    void ProjectBuild::Build()
    {
        if (ProjectManager::Get().GetLoadedProject())
        {
            LOG_WARN("Starting project build");
            buildStarted = true;
            buildDone = false;
            SET_IM_WINDOW_VISIBLE("BuildProgressBar", true);

            //create project build script temp
            KE::File buildScript;
            buildScript.Open(ProjectManager::Get().GetLoadedProject()->properties.path + "\\premake5.lua", KE::ModeFlags::WRITE);
            buildScript.Write(FileGenerator::GenerateBuildScriptFile(ProjectManager::Get().GetLoadedProject()->properties.name));
            buildScript.Close();

            // generate build files
            generatingBuildFiles = true;
            std::thread generateFilesThread(GenerateBuildFiles, std::ref(filesGenerated));
            generateFilesThread.detach();
        }
    }

    void ProjectBuild::GenerateBuildFiles(std::atomic<bool> &filesGenerated)
    {
        std::string command = "call " + KE::Core::WINDOWS_TOOLS_DIR + "premake5.exe vs2022";
        int result = std::system(command.c_str());
        if (result != 0)
        {
            buildDone = true;
            buildStarted = false;
            LOG_ERROR("Error to generate build files");
            SET_IM_WINDOW_VISIBLE("BuildProgressBar", false);
            BuildErrorDialog::SetShow();
            return;
        }

        filesGenerated = true;
    }

    void ProjectBuild::Compile(std::atomic<bool> &compileDone)
    {
        std::string projectName = ProjectManager::Get().GetLoadedProject()->properties.name;
        std::string projectSolution = projectName + ".sln";

        std::string command =
            "\"\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" && "
        "msbuild \"" + projectSolution + "\" /p:Configuration=Release /p:Platform=x64\"";

        int result = std::system(command.c_str());
        if (result != 0)
        {
            LOG_ERROR("Error to compile project files");
            BuildErrorDialog::SetShow();
        }

        compileDone = true;
    }
}
