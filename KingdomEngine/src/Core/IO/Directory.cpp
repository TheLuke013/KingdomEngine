#include "KingdomEngine/Core/IO/Directory.h"
#include "KingdomEngine/Core/Log.h"

#include <cstdlib>

namespace KE
{
    Directory::Directory()
    {

    }

    Directory::~Directory()
    {

    }

    void Directory::Open(const std::string& path)
    {
        if (!DirExists(path))
        {
            LOG_ERROR("Directory does not exist: " + path);
            return;
        }

        #ifdef _WIN32
            std::string command = "start " + path;
        #elif __APPLE__
            std::string command = "open " + path;
        #elif __linux__
            std::string command = "xdg-open " + path;
        #else
            LOG_ERROR("Unsupported platform for opening directories");
            return;
        #endif
        int result = std::system(command.c_str());
        if (result != 0)
        {
            LOG_ERROR("Failed to open directory: " + path);
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
            std::string errMsg = "Error removing: " + path + " - " + e.what();
            LOG_ERROR(errMsg);
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
            std::string errMsg = "Error renaming: " + from + " to " + to + " - " + e.what();
            LOG_ERROR(errMsg);
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
            std::string errMsg = "Error copying: " + std::string(e.what());
            LOG_ERROR(errMsg);
        }
    }

    void Directory::Create(const std::string& path)
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
        catch (const std::filesystem::filesystem_error& e)
        {
            std::string errMsg = "Error creating directory: " + path + " - " + e.what();
            LOG_ERROR(errMsg);
        }
    }

    bool Directory::CurrentIsDir() const
    {
        auto currentDir = std::filesystem::current_path();
        return std::filesystem::is_directory(currentDir);
    }
}