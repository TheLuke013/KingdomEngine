#ifndef CORE_H
#define CORE_H

#include "KingdomEngine/Core/IO/OS.h"

#include <string>

namespace KE
{
    namespace Core
    {
        inline const std::string ENGINE_CORE_VERSION = "1.0";

        inline const std::string KE_DIRECTORY = OS::GetUserDir() + "\\KingdomEngine";

        inline const std::string RESOURCES_DIR = OS::GetCurrentDir() + "\\..\\resources";
        inline const std::string FONTS_DIR = RESOURCES_DIR + "\\fonts";
        inline const std::string SHADERS_GL2 = RESOURCES_DIR + "\\shaders\\gl2";
        inline const std::string SHADERS_GL3 = RESOURCES_DIR + "\\shaders\\gl3";
    };
}

#endif
