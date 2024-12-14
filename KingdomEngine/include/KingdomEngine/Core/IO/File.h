#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <string>

namespace KE
{
    enum class ModeFlags
    {
        READ = std::ios::in,
        WRITE = std::ios::out | std::ios::trunc,
        READ_WRITE = std::ios::in | std::ios::out
    };

	class File
	{
	public:
		File();
		~File();

		void Open(const std::string& filename, ModeFlags mode);
		void Write(const std::string& data);
		void Remove();
		void Copy(const std::string& from, const std::string& to);
		std::string Read();
		void Close();

		bool IsOpen() const { return file.is_open(); };
		static bool Exists(const std::string& filename);
		std::string GetFilename() const { return filename; };
		std::fstream& GetFile() { return file; }

	private:
		std::fstream file;
		std::string filename;

	};
}

#endif
