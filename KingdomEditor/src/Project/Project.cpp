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
		kepDict.Add("window_title", properties.name);
		kepDict.Add("window_width", properties.windowProperties.width);
		kepDict.Add("window_height", properties.windowProperties.height);
        projectJson.AddDicionary("project", kepDict);
        WriteProjectFile();
    }

    void Project::SaveKepFile()
    {
        projectJson.SetValue("project", "name", properties.name);
        projectJson.SetValue("project", "gl_version", properties.glVersion);
        projectJson.SetValue("project", "background_color", properties.backgroundColor.GetHex());
		projectJson.SetValue("project", "window_title", properties.windowProperties.title);
		projectJson.SetValue("project", "window_width", properties.windowProperties.width);
		projectJson.SetValue("project", "window_height", properties.windowProperties.height);

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

        std::string name = projectJson.GetValue<std::string>("project", "name", "Project Name");
        int glVersion = projectJson.GetValue<int>("project", "gl_version", 1);
        std::string backgroundColor = projectJson.GetValue<std::string>("project", "background_color", "#000000");
		
		std::string windowTitle = projectJson.GetValue<std::string>("project", "window_title", "Window Title");
		int windowWidth = projectJson.GetValue<int>("project", "window_width", 1024);
		int windowHeight = projectJson.GetValue<int>("project", "window_height", 600);

        properties.name = name;
        properties.glVersion = glVersion;
        properties.backgroundColor.FromHex(backgroundColor);
		
		properties.windowProperties.title = windowTitle;
		properties.windowProperties.width = windowWidth;
		properties.windowProperties.height = windowHeight;

        if (glVersion == KE::GLVersion::OpenGL2)
        {
            DISPATCH_EVENT(KE::EventType::LoadGL2);
            LOG_WARN("Switching OpenGL version to OpenGL 2.1!");
        }
        else if (glVersion == KE::GLVersion::OpenGL3)
        {
            DISPATCH_EVENT(KE::EventType::LoadGL3);
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
