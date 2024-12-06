#ifndef PROJECT_H
#define PROJECT_H

#include <KingdomEngine/KingdomEngine.h>

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
