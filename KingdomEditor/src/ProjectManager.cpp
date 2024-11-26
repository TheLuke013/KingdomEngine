#include "KingdomEditor/ProjectManager.h"

namespace Editor
{
    ProjectManager& ProjectManager::Get()
	{
		static ProjectManager* instance = new ProjectManager();
		return *instance;
	}

	void ProjectManager::LoadProject(Project& project)
	{
        if (loadedProject)
        {
            UnloadProject();
        }

        loadedProject = new Project(project.properties.name, project.properties.glVersion);
	}

    void ProjectManager::UnloadProject()
    {

    }
}
