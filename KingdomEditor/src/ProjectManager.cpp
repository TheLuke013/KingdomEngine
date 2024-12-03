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
        WriteProjectFile();
    }

    void ProjectManager::OpenProjectsFile()
    {
        if (!projectsFile.Exists(PROJECTS_FILE))
        {
            WriteProjectFile();
        }
        else
        {
            projectsFile.Open(PROJECTS_FILE, KE::ModeFlags::READ);
            std::string fileContent = projectsFile.Read();
            projectsFile.Close();

            if (fileContent.empty())
            {
                WriteProjectFile();
            }
        }

        projectsFile.Open(PROJECTS_FILE, KE::ModeFlags::READ);
        projectsJson.Parse(projectsFile.Read(), true);
        projectsFile.Close();

        for (auto it = projectsJson.GetData().MemberBegin(); it != projectsJson.GetData().MemberEnd(); ++it)
        {
            if (it->value.IsObject())
            {
                auto &obj = it->value;

                int glVersion = 0;
                std::string kepFile = "";
                std::string path = "";

                if (obj.HasMember("path") && obj["path"].IsString() &&
                    obj.HasMember("kep_file") && obj["kep_file"].IsString() &&
                    obj.HasMember("gl_version") && obj["gl_version"].IsInt())
                {
                    glVersion = obj["gl_version"].GetInt();
                    kepFile = obj["kep_file"].GetString();
                    path = obj["path"].GetString();

                    Project project(it->name.GetString(), path, kepFile, glVersion);
                    PushProject(project);
                }
                else
                {
                    std::string errMsg = "Object is missing members: " + std::string(it->name.GetString());
                    LOG_ERROR(errMsg);
                }
            }
            else
            {
                std::string errMsg = "it is not a json object: " + std::string(it->name.GetString());
                LOG_ERROR(errMsg);
            }
        }
    }

    void ProjectManager::AddProject(Project &project)
    {
        //create project dictionary
        KE::Dictionary projectDict;
        projectDict.Add("path", project.properties.path);
        projectDict.Add("kep_file", project.properties.kepFile);
        projectDict.Add("gl_version", project.properties.glVersion);
        projectsJson.AddDicionary(project.properties.name, projectDict);

        //create project directory
        KE::Directory projDir;
        if (!projDir.DirExists(project.properties.path))
        {
            projDir.Create(project.properties.path);
            LOG_INFO("Project directory created");

            //create project kep file
            KE::File kepFile;
            std::string kepFilePath = project.properties.path + "\\" + project.properties.kepFile;
            kepFile.Open(kepFilePath, KE::ModeFlags::WRITE);
            kepFile.Close();
        }
        else
        {
            LOG_ERROR("Project directory already exists");
        }

        PushProject(project);
    }

    void ProjectManager::LoadProject(const std::string &projectName)
    {
        if (loadedProject)
        {
            UnloadProject();
        }

        auto it = projectsMap.find(projectName);
        if (it != projectsMap.end())
        {
            loadedProject = it->second;
        }
        else
        {
            LOG_ERROR("Project not found");
        }
    }

    void ProjectManager::UnloadProject()
    {
        delete loadedProject;
        loadedProject = nullptr;
    }

    void ProjectManager::RemoveProject(const std::string &projectName)
    {
        if (loadedProject && loadedProject->properties.name == projectName)
        {
            UnloadProject();
        }

        auto it = projectsMap.find(projectName);
        if (it != projectsMap.end())
        {
            Project *projectToRemove = it->second;
            projectsMap.erase(it);

            auto projIt = std::find(projects.begin(), projects.end(), projectToRemove);
            if (projIt != projects.end())
            {
                projects.erase(projIt);
            }

            if (projectsJson.GetData().HasMember(projectName.c_str()))
            {
                projectsJson.GetData().RemoveMember(projectName.c_str());
            }

            delete projectToRemove;

            WriteProjectFile();
        }
        else
        {
            LOG_ERROR("Project not found");
        }
    }

    void ProjectManager::WriteProjectFile()
    {
        projectsFile.Open(PROJECTS_FILE, KE::ModeFlags::WRITE);
        projectsFile.Write(projectsJson.Stringify());
        projectsFile.Close();
    }

    void ProjectManager::PushProject(Project &project)
    {
        Project *proj = new Project(project.properties.name, project.properties.path, project.properties.kepFile, project.properties.glVersion);
        projects.push_back(proj);
        projectsMap[project.properties.name] = proj;
    }
}
