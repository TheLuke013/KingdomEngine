#include "KingdomEditor/Project/ProjectBuild.h"

namespace Editor
{
    float ProjectBuild::buildProgress = 0.0f;
    bool ProjectBuild::buildDone = false;
    bool ProjectBuild::buildStarted = false;
    std::atomic<bool> ProjectBuild::cmakeDone = false;

    void ProjectBuild::Build()
    {
        if (ProjectManager::Get().GetLoadedProject())
        {
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
            std::thread cmakeThread(RunCMake, std::ref(cmakeDone));
            cmakeThread.detach();
        }
    }

    void ProjectBuild::RunCMake(std::atomic<bool>& buildDone)
    {
        int result = std::system("cmake ..");
        if (result != 0)
        {
            LOG_ERROR("Error to generate CMAKE Files");
        }
        cmakeDone = true;
    }
}