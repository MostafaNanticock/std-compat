#include <testing.h>

#include <fs_tests_common/test_utils.h>

#include <filesystem>
#include <fstream>

bool test_status()
{
    STDC::Testing::FileSystemTestCase testCase("test_dir");
    std::filesystem::path filePath = testCase.path() / "file.txt";

    std::ofstream ofs = STDC::Testing::open_stream_from_path<std::ofstream>(filePath);
    if (!ofs)
        return false;
    ofs << "status test\n";
    ofs.close();

    std::error_code ec;
    std::filesystem::file_status st = std::filesystem::status(filePath, ec);
    if (ec || !std::filesystem::is_regular_file(st))
        return false;

    std::filesystem::permissions(filePath, std::filesystem::perms::owner_read, std::filesystem::perm_options::add, ec);

    auto t = std::filesystem::last_write_time(filePath, ec);
    std::filesystem::last_write_time(filePath, t, ec);

    if (std::filesystem::absolute(filePath, ec).empty() || std::filesystem::canonical(filePath, ec).empty())
        return false;

    if (!std::filesystem::equivalent(filePath, filePath, ec))
        return false;

    std::filesystem::space_info si = std::filesystem::space(testCase.path(), ec);
    if (ec || si.capacity == 0)
        return false;

    if (!std::filesystem::exists(std::filesystem::temp_directory_path(), ec))
        return false;
    if (!std::filesystem::is_regular_file(filePath, ec) || !std::filesystem::is_directory(testCase.path(), ec))
        return false;

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_status);
}
