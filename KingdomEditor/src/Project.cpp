#include "KingdomEditor/Project.h"

namespace Editor
{
    Project::Project(const std::string& name, int glVersion)
    {
        properties.name = name;
        properties.glVersion = glVersion;
    }

    Project::~Project()
    {

    }
}
