#include "KingdomEngine/Core/IO/OS.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	std::vector<std::string> OS::GetFilesWithExtension(const std::string& directory, const std::string& extension)
	{
        std::vector<std::string> filePaths;

        try
        {
            for (const auto& entry : std::filesystem::directory_iterator(directory))
            {
                if (entry.is_regular_file() && entry.path().extension() == extension)
                {
                    filePaths.push_back(entry.path().string());
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::string errorMsg = "Error accessing directory: " + std::string(e.what());
            LOG_ERROR(errorMsg);
        }

        return filePaths;
	}

	#if defined(_WIN32)
        #include <windows.h>
        #include <shlobj.h>
    #elif defined(__APPLE__) || defined(__MACH__)
        #include <pwd.h>
        #include <unistd.h>
    #elif defined(__linux__)
        #include <cstdlib>
        #include <pwd.h>
        #include <unistd.h>
    #endif

	std::string OS::GetUserDir()
	{
        #if defined(_WIN32)
            char path[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, path)))
            {
                return std::string(path);
            }
            return "";

        #elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            const char* home_dir = getenv("HOME");
            if (!home_dir)
            {
                home_dir = getpwuid(getuid())->pw_dir;
            }

            std::string documents_folder = std::string(home_dir) + "/Documents";

        #if defined(__linux__)
            const char* xdg_documents_dir = getenv("XDG_DOCUMENTS_DIR");
            if (xdg_documents_dir)
            {
                documents_folder = std::string(xdg_documents_dir);
            }
        #endif

            return documents_folder;
        #else
            return "";
        #endif
	}
}
