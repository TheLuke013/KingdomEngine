#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <KingdomEngine/KingdomEngine.h>

#include "KingdomEditor/Project.h"

namespace Editor
{
	class ProjectManager
	{
	public:
		static ProjectManager& Get();

		void LoadProject(Project& project);
		void UnloadProject();

		Project* GetLoadedProject() { return loadedProject; }

	private:
		ProjectManager() {}

        Project* loadedProject;

	};
}

#endif
