#include "KingdomEditor/Project/Project.h"

namespace Editor
{
    Project::Project(const std::string &name, const std::string &path, const std::string &kepFile)
    {
        properties.name = name;
        properties.path = path;
        properties.kepFile = kepFile;
    }

    Project::~Project()
    {
    }

    void Project::CreateKepFile()
    {
        KE::Dictionary kepDict;
        kepDict.Add("name", properties.name);
        kepDict.Add("gl_version", properties.glVersion);
        kepDict.Add("background_color", properties.backgroundColor.GetHex());
        projectJson.AddDicionary("project", kepDict);
        WriteProjectFile();
    }

    void Project::SaveKepFile()
    {
        projectJson.SetValue("project", "name", properties.name);
        projectJson.SetValue("project", "gl_version", properties.glVersion);
        projectJson.SetValue("project", "background_color", properties.backgroundColor.GetHex());

        WriteProjectFile();
    }

    void Project::LoadKepFile()
    {
        if (!projectFile.Exists(properties.path + "\\" + properties.kepFile))
        {
            WriteProjectFile();
        }
        else
        {
            projectFile.Open(properties.path + "\\" + properties.kepFile, KE::ModeFlags::READ);
            std::string fileContent = projectFile.Read();
            projectFile.Close();

            if (fileContent.empty())
            {
                WriteProjectFile();
            }
        }

        projectFile.Open(properties.path + "\\" + properties.kepFile, KE::ModeFlags::READ);
        projectJson.Parse(projectFile.Read(), true);
        projectFile.Close();

        std::string name = projectJson.GetValue<std::string>("project", "name", "My Project");
        int glVersion = projectJson.GetValue<int>("project", "gl_version", 1);
        std::string backgroundColor = projectJson.GetValue<std::string>("project", "background_color", "#000000");

        properties.name = name;
        properties.glVersion = glVersion;
        properties.backgroundColor.FromHex(backgroundColor);

        if (glVersion == KE::GLVersion::OpenGL2)
        {
            DISPATCH_EVENT(KE::EventType::LOAD_OPENGL2);
            LOG_WARN("Switching OpenGL version to OpenGL 2.1!");
        }
        else if (glVersion == KE::GLVersion::OpenGL3)
        {
            DISPATCH_EVENT(KE::EventType::LOAD_OPENGL3);
            LOG_WARN("Switching OpenGL version to OpenGL 3.3!");
        }
        else
        {
            LOG_ERROR("Invalid OpenGL version in project JSON");
        }
    }

    void Project::WriteProjectFile()
    {
        projectFile.Open(properties.path + "\\" + properties.kepFile, KE::ModeFlags::WRITE);
        projectFile.Write(projectJson.Stringify());
        projectFile.Close();
    }
}
