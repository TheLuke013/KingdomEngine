#ifndef BUILD_PROGRESS_H
#define BUILD_PROGRESS_H

#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Project/ProjectManager.h"

#include <thread>
#include <atomic>

namespace Editor
{
    class ProjectBuild
    {
    public:
        static void Build();
        static void RunCMake(std::atomic<bool>& buildDone);
        static void RunMSBUILD(std::atomic<bool>& msbuildDone);

        static float buildProgress;
        static bool buildDone;
        static bool buildStarted;
        static bool runningCmake;
        static std::atomic<bool> cmakeDone;
        static std::atomic<bool> msbuildDone;

    };
}

#endif
