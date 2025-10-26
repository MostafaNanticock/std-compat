#pragma once

#include <filesystem>
#include <system_error>

namespace STDC
{
namespace Testing
{
    class FileSystemTestCase
    {
    public:
        explicit FileSystemTestCase(const std::filesystem::path &rootPath) : root(rootPath)
        {
            std::error_code ec;
            std::filesystem::remove_all(root, ec);
            std::filesystem::create_directories(root, ec);
        }

        ~FileSystemTestCase()
        {
            std::error_code ec;
            std::filesystem::remove_all(root, ec);
        }

        const std::filesystem::path &path() const
        {
            return root;
        }

    private:
        std::filesystem::path root;
    };

    template <typename T>
    T open_stream_from_path(const std::filesystem::path &path, std::ios::openmode mode = std::ios::in)
    {
        return T(path.c_str(), mode);
    }
} // namespace Testing
} // namespace STDC
