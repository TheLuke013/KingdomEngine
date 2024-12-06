#include "KingdomEngine/Core/IO/File.h"
#include "KingdomEngine/Core/Log.h"

#include <filesystem>

namespace KE
{
	File::File()
	{

	}

	File::~File()
	{
		if (file.is_open())
			file.close();
	}

	void File::Open(const std::string& filename, ModeFlags mode)
	{
		this->filename = filename;
		file.open(filename, static_cast<std::ios::openmode>(mode));

		if (!file.is_open())
		{
			LOG_ERROR("Error opening file:" + filename);
		}
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

	void File::Remove()
	{
	    if (file.is_open())
        {
            file.close();
        }

        if (std::filesystem::exists(filename))
        {
            if (!std::filesystem::remove(filename))
            {
                LOG_ERROR("Error to remove file");
            }
        }
        else
        {
            LOG_ERROR("Error: File is not open");
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

	bool File::Exists(const std::string& filename)
	{
	    std::fstream file;
	    file.open(filename, std::ios::in);

		if (!file.is_open())
		{
			return false;
		}
		return file.good();
	}
}
