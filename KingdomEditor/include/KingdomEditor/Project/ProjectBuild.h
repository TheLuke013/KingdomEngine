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
        static void GenerateBuildFiles(std::atomic<bool>& filesGenerated);
        static void Compile(std::atomic<bool>& compileDone);

        static float buildProgress;
        static bool buildDone;
        static bool buildStarted;
        static bool generatingBuildFiles;
        static std::atomic<bool> filesGenerated;
        static std::atomic<bool> compileDone;

    };
}

#endif
