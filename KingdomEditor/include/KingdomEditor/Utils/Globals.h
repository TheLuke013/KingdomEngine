#ifndef GLOBALS_H
#define GLOBALS_H



namespace Editor
{
    namespace Globals
    {
        inline bool PROJECT_CHANGED = false;
		inline bool CAN_SAVE_FILE = false;

        inline const std::string KE_PROJECTS_DIRECTORY = KE::Core::KE_DIRECTORY + "\\projects";
        inline const std::string PROJECTS_FILE = KE::Core::KE_DIRECTORY + "\\projects.json";
    }
}

#endif
