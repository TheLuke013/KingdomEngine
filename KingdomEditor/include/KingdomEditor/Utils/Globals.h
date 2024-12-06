#ifndef GLOBALS_H
#define GLOBALS_H

#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
    namespace Globals
    {
        inline bool PROJECT_CHANGED = false;

        inline const std::string KE_PROJECTS_DIRECTORY = KE::Core::KE_DIRECTORY + "\\projects";
        inline const std::string PROJECTS_FILE = KE::Core::KE_DIRECTORY + "\\projects.json";
    }
}

#endif
