#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <KingdomEngine/KingdomEngine.h>
#include "KingdomEditor/Project/Project.h"

#include <unordered_map>

namespace Editor
{
	class ProjectManager
	{
	public:
		static ProjectManager& Get();

		void SaveProjectsFile();
		void OpenProjectsFile();
		void AddProject(Project& project);
		void LoadProject(const std::string& projectName);
		void UnloadProject();
		void RemoveProject(const std::string& projectName);

		std::vector<Project*>& GetProjects() { return projects; }
		Project* GetLoadedProject() { return loadedProject; }
		KE::JSON& GetJson() { return projectsJson; }

	private:
		ProjectManager()
            : loadedProject(nullptr)
		{}

		void WriteProjectFile();
		void PushProject(Project& project);

		std::vector<Project*> projects;
		std::unordered_map<std::string, Project*> projectsMap;
        Project* loadedProject;
        KE::JSON projectsJson;
		KE::File projectsFile;

	};
}

#endif
