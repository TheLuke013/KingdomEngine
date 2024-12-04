#ifndef GLOBALS_H
#define GLOBALS_H

#include <KingdomEngine/KingdomEngine.h>

inline const std::string KE_DIRECTORY = KE::OS::GetUserDir() + "\\KingdomEngine";
inline const std::string KE_PROJECTS_DIRECTORY = KE_DIRECTORY + "\\projects";
inline const std::string PROJECTS_FILE = KE_DIRECTORY + "\\projects.json";

inline const std::string RESOURCES_DIR = KE::OS::GetCurrentDir() + "\\..\\resources";
inline const std::string FONTS_DIR = RESOURCES_DIR + "\\fonts";
inline const std::string SHADERS_GL2 = RESOURCES_DIR + "\\shaders\\gl2";
inline const std::string SHADERS_GL3 = RESOURCES_DIR + "\\shaders\\gl3";

#endif
