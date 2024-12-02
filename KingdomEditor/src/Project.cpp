#include "KingdomEditor/Project.h"

namespace Editor
{
    Project::Project(const std::string& name, const std::string& path, const std::string& kepFile, int glVersion)
    {
        properties.name = name;
        properties.path = path;
        properties.kepFile = kepFile;
        properties.glVersion = glVersion;
    }

    Project::~Project()
    {

    }
}
