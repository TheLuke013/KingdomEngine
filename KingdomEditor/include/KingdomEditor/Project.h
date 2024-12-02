#ifndef PROJECT_H
#define PROJECT_H

#include <KingdomEngine/KingdomEngine.h>

namespace Editor
{
    struct ProjectProperties
    {
        std::string name;
        std::string path;
        std::string kepFile;
        int glVersion;
    };

    class Project
    {
    public:
        Project(const std::string& name, const std::string& path, const std::string& kepFile, int glVersion);
        ~Project();

        ProjectProperties properties;
    };
}

#endif
