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

        static float buildProgress;
        static bool buildDone;
        static bool buildStarted;
        static std::atomic<bool> cmakeDone;

    private:
        static void RunCMake(std::atomic<bool>& buildDone);
    };
}

#endif
