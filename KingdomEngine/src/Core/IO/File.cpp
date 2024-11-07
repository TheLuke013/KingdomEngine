#include "KingdomEngine/Core/IO/File.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
	File::File(const std::string& filename)
		: filename(filename)
	{
		
	}

	File::~File()
	{
		if (file.is_open())
			file.close();
	}

	bool File::Open(const std::string& filename, std::ios::openmode mode)
	{
		this->filename = filename;
		file.open(filename, mode);

		if (!file.is_open()) 
		{
			LOG_ERROR("Error opening file:" + filename);
			return false;
		}
		return true;
	}

	void File::Write(const std::string& data)
	{
		if (file.is_open() && file.good()) 
		{
			file << data;
		}
		else 
		{
			LOG_ERROR("Error: File is not open or there is a problem writing");
		}
	}

	std::string File::Read()
	{
		if (file.is_open() && file.good()) 
		{
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return content;
		}

		LOG_ERROR("Error: File is not open or there is a problem reading it");
		return "";
	}

	void File::Close()
	{
		if (file.is_open()) 
			file.close();
	}
}