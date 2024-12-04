#include "KingdomEditor/Project/ProjectBuild.h"
#include "KingdomEditor/DialogBox/BuildErrorDialogBox.h"

namespace Editor
{
    float ProjectBuild::buildProgress = 0.0f;
    bool ProjectBuild::buildDone = false;
    bool ProjectBuild::buildStarted = false;
    bool ProjectBuild::runningCmake = false;
    std::atomic<bool> ProjectBuild::cmakeDone = false;
    std::atomic<bool> ProjectBuild::msbuildDone = false;

    void ProjectBuild::Build()
    {
        if (ProjectManager::Get().GetLoadedProject())
        {
            LOG_WARN("Starting project build");
            buildStarted = true;
            buildDone = false;
            SET_IM_WINDOW_VISIBLE("BuildProgressBar", true);

            // check build dir and change current dir
            KE::Directory buildDir;
            std::string buildDirStr = KE::OS::GetCurrentDir() + "\\build";
            if (!buildDir.DirExists(buildDirStr))
                buildDir.Create(buildDirStr);

            KE::OS::SetCurrentDir(buildDirStr);

            // generate build files
            runningCmake = true;
            std::thread cmakeThread(RunCMake, std::ref(cmakeDone));
            cmakeThread.detach();
        }
    }

    void ProjectBuild::RunCMake(std::atomic<bool> &buildDone)
    {
        int result = std::system("cmake ..");
        if (result != 0)
        {
            LOG_ERROR("Error to generate CMAKE Files");
        }
        cmakeDone = true;
    }

    void ProjectBuild::RunMSBUILD(std::atomic<bool> &msbuildDone)
    {
        std::string projectName = ProjectManager::Get().GetLoadedProject()->properties.name;
        projectName.erase(std::remove(projectName.begin(), projectName.end(), ' '), projectName.end());
        std::string projectSolution = projectName + ".sln";

        std::string command =
            "\"\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\Tools\\VsDevCmd.bat\" && "
        "msbuild \"" + projectSolution + "\" /p:Configuration=Release /p:Platform=x64\"";

        int result = std::system(command.c_str());
        if (result != 0)
        {
            LOG_ERROR("Error executing MSBuild");
            BuildErrorDialog::SetShow();
        }

        msbuildDone = true;
    }
}