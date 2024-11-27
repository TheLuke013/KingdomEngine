#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

namespace KE
{
    enum class ModeFlags
    {
        READ = std::ios::in,
        WRITE = std::ios::out,
        READ_WRITE = std::ios::in | std::ios::out | std::ios::app
    };

	class File
	{
	public:
		File();
		~File();

		void Open(const std::string& filename, ModeFlags mode);
		void Write(const std::string& data);
		std::string Read();
		void Close();

		bool IsOpen() const { return file.is_open(); };
		static bool Exists(const std::string& filename);
		std::string GetFilename() const { return filename; };

	private:
		std::fstream file;
		std::string filename;

	};
}

#endif
