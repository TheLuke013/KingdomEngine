#include "KingdomEngine/Core/IO/IOUtils.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	std::vector<std::string> IOUtils::GetFilesWithExtension(const std::string& directory, const std::string& extension)
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
}