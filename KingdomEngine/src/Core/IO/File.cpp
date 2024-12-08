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

	void File::Copy(const std::string& from, const std::string& to)
	{
        std::ifstream fileToCopy(from, std::ios::binary);
        if (!fileToCopy)
        {
            LOG_ERROR("Error opening source file: " + from);
            return;
        }

        std::ofstream fileDest(to, std::ios::binary);
        if (!fileDest)
        {
            LOG_ERROR("Error creating destination file: " + to);
            return;
        }

        fileDest << fileToCopy.rdbuf();

        LOG_INFO("File successfully copied from " + from + " to " + to);
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
