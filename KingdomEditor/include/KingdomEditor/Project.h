#ifndef PROJECT_H
#define PROJECT_H

#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
    struct ProjectProperties
    {
        std::string name = "New Project";
        int glVersion = KE::Renderer::GetVersion().glVersion;
    };

    class Project
    {
    public:
        Project(const std::string& name, int glVersion);
        ~Project();

        ProjectProperties properties;
    };
}

#endif
