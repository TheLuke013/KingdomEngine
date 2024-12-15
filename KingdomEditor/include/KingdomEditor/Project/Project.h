#ifndef PROJECT_H
#define PROJECT_H

#include <KingdomEngine/Core/Core.h>
#include <KingdomEngine/Core/Log.h>
#include <KingdomEngine/Core/Event.h>
#include <KingdomEngine/Core/IO/Directory.h>
#include <KingdomEngine/Core/IO/File.h>
#include <KingdomEngine/Core/Dictionary.h>
#include <KingdomEngine/Core/Color.h>
#include <KingdomEngine/Core/JSON.h>
#include <KingdomEngine/Core/Window.h>
#include <KingdomEngine/Renderer/Renderer.h>

namespace Editor
{
    struct ProjectProperties
    {
        std::string name = "My Project";
        std::string path = "";
        std::string kepFile = "";
        std::string engineCoreVersion = KE::Core::ENGINE_CORE_VERSION;
        KE::Color backgroundColor = KE::Renderer::GetClearColor();
        int glVersion = KE::GLVersion::OpenGL2;
		KE::WindowProperties windowProperties;
    };

    class Project
    {
    public:
        Project(const std::string& name, const std::string& path, const std::string& kepFile);
        ~Project();

        void CreateKepFile();
        void SaveKepFile();
        void LoadKepFile();

        ProjectProperties properties;
        KE::JSON projectJson;
		KE::File projectFile;

    private:
        void WriteProjectFile();
    };
}

#endif
