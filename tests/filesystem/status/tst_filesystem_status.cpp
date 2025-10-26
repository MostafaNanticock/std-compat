#include <testing.h>

#include <filesystem>

bool test_status()
{
    std::filesystem::path p1{"test_dir"};
    std::filesystem::path p2{"test_dir/file.txt"};

    std::filesystem::file_status st = std::filesystem::status(p2);
    if (!std::filesystem::is_regular_file(st))
        return false;

    std::filesystem::permissions(p2, std::filesystem::perms::owner_read, std::filesystem::perm_options::add);

    auto t = std::filesystem::last_write_time(p2);
    std::filesystem::last_write_time(p2, t);

    if (std::filesystem::absolute(p2).empty() || std::filesystem::canonical(p2).empty())
        return false;
    if (!std::filesystem::equivalent(p2, p2))
        return false;

    std::filesystem::space_info si = std::filesystem::space(p1);
    if (si.capacity == 0)
        return false;

    if (!std::filesystem::exists(std::filesystem::temp_directory_path()))
        return false;
    if (!std::filesystem::is_regular_file(p2) || !std::filesystem::is_directory(p1))
        return false;

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_status);
}
