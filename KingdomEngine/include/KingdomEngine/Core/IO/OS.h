#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <filesystem>
#include <vector>
#include <string>

namespace KE
{
	class OS
	{
	public:
		static std::vector<std::string> GetFilesWithExtension(const std::string& directory, const std::string& extension);
		static std::string GetUserDir();
		static std::string GetCurrentDir() { return std::filesystem::current_path().string(); };
	};
}

#endif
