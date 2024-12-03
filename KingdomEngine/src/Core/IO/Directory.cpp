#include "KingdomEngine/Core/IO/Directory.h"
#include "KingdomEngine/Core/Log.h"

namespace KE
{
    Directory::Directory()
    {
    }

    Directory::~Directory()
    {
    }

    void Directory::Open(const std::string &path)
    {
        try
        {
            if (DirExists(path))
            {
                std::filesystem::current_path(path);
                LOG_WARN("Changed current directory to: " + path);
            }
            else
            {
                LOG_ERROR("Directory does not exist: " + path);
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            LOG_ERROR("Failed to change directory to: " + path + " - " + e.what());
        }
    }

    void Directory::Remove(const std::string &path)
    {
        try
        {
            std::filesystem::remove_all(path);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            LOG_ERROR("Error removing: " + path + " - " + e.what());
        }
    }

    void Directory::Rename(const std::string &from, const std::string &to)
    {
        try
        {
            std::filesystem::rename(from, to);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            LOG_ERROR("Error renaming: " + from + " to " + to + " - " + e.what());
        }
    }

    void Directory::Copy()
    {
        try
        {
            auto currentDir = std::filesystem::current_path();
            std::filesystem::copy(currentDir, currentDir.string() + "_copy",
                                  std::filesystem::copy_options::recursive);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            LOG_ERROR("Error copying: " + std::string(e.what()));
        }
    }

    void Directory::Create(const std::string &path)
    {
        try
        {
            if (!DirExists(path))
            {
                std::filesystem::create_directories(path);
            }
            else
            {
                LOG_WARN("Directory already exists: " + path);
            }
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            LOG_ERROR("Error creating directory: " + path + " - " + e.what());
        }
    }

    bool Directory::CurrentIsDir() const
    {
        auto currentDir = std::filesystem::current_path();
        return std::filesystem::is_directory(currentDir);
    }
}