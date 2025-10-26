#pragma once

#include <filesystem>
#include <system_error>

namespace STDC
{
namespace Testing
{
    namespace internal
    {
        template <typename T, typename CharT>
        T open_stream_impl(const std::filesystem::path &path, std::ios::openmode mode, std::true_type);

        template <typename T, typename CharT>
        T open_stream_impl(const std::filesystem::path &path, std::ios::openmode mode, std::false_type);
    } // namespace internal

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
        typedef typename T::char_type CharT;

        // Narrow stream
        return STDC::Testing::internal::open_stream_impl<T, CharT>(path, mode, typename std::is_same<CharT, char>::type());
    }
} // namespace Testing
} // namespace STDC

// Overload for narrow streams
template <typename T, typename CharT>
T STDC::Testing::internal::open_stream_impl(const std::filesystem::path &path, std::ios::openmode mode, std::true_type)
{
    return T(path.string(), mode);
}

// Overload for wide streams
template <typename T, typename CharT>
T STDC::Testing::internal::open_stream_impl(const std::filesystem::path &path, std::ios::openmode mode, std::false_type)
{
    return T(path.wstring(), mode);
}
