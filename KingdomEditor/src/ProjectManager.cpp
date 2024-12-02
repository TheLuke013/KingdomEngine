#include "KingdomEditor/ProjectManager.h"
#include "KingdomEditor/Utils/Globals.h"

namespace Editor
{
    ProjectManager &ProjectManager::Get()
    {
        static ProjectManager *instance = new ProjectManager();
        return *instance;
    }

    void ProjectManager::SaveProjectsFile()
    {
        projectsFile.Open(KE_DIRECTORY + "\\projects.json", KE::ModeFlags::READ_WRITE);
        projectsFile.Write(projectsJson.Stringify());
        projectsFile.Close();
    }

    void ProjectManager::AddProject(Project &project)
    {
        KE::Dictionary projectDict;
        projectDict.Add("path", project.properties.path);
        projectDict.Add("kep_file", project.properties.kepFile);
        projectDict.Add("gl_version", project.properties.glVersion);
        projectsJson.AddDicionary(project.properties.name, projectDict);
    }

    void ProjectManager::LoadProject(Project &project)
    {
        if (loadedProject)
        {
            UnloadProject();
        }

        loadedProject = new Project(
            project.properties.name,
            project.properties.path,
            project.properties.kepFile,
            project.properties.glVersion);
    }

    void ProjectManager::UnloadProject()
    {
        delete loadedProject;
        loadedProject = nullptr;
    }
}
