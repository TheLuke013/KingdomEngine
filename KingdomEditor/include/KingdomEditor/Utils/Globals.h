#ifndef GLOBALS_H
#define GLOBALS_H

#include <KingdomEngine/KingdomEngine.h>

inline const std::string KE_DIRECTORY = KE::OS::GetUserDir() + "\\KingdomEngine";
inline const std::string KE_PROJECTS_DIRECTORY = KE_DIRECTORY + "\\projects";

inline const std::string RESOURCES_DIR = "..\\resources";
inline const std::string FONTS_DIR = RESOURCES_DIR + "\\fonts";
inline const std::string PROJECTS_FILE = KE_DIRECTORY + "\\projects.json";

#endif
