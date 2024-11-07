#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <filesystem>
#include <vector>
#include <string>

namespace KE
{
	class IOUtils
	{
	public:
		static std::vector<std::string> GetFilesWithExtension(const std::string& directory, const std::string& extension);
	};
}

#endif