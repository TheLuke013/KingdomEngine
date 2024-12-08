#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <filesystem>

namespace KE
{
    class Directory
    {
    public:
        Directory();
        ~Directory();

        void Open(const std::string& path);
        void Remove(const std::string& path);
        void Rename(const std::string& from, const std::string& to);
        void Copy(const std::string& from, const std::string& to);
        void Create(const std::string& path);
        bool CurrentIsDir() const;
        bool DirExists(const std::string& path) { return std::filesystem::exists(path) && std::filesystem::is_directory(path); }
        std::string GetCurrentDir() { return std::filesystem::current_path().string(); }

    private:


    };
}

#endif
