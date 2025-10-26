#include <testing.h>

#include <fs_tests_common/test_utils.h>

#include <filesystem>
#include <fstream>

bool test_status()
{
    std::error_code ec;
    const std::filesystem::path root = "test_dir";
    const std::filesystem::path filePath = root / "file.txt";

    // Setup: ensure directory and file exist
    std::filesystem::remove_all(root, ec);
    std::filesystem::create_directories(root, ec);

    std::ofstream ofs(filePath);
    if (!ofs)
    {
        cleanUpTestCase(root);
        return false;
    }
    ofs << "status test\n";
    ofs.close();

    // Check status
    std::filesystem::file_status st = std::filesystem::status(filePath, ec);
    if (ec || !std::filesystem::is_regular_file(st))
    {
        cleanUpTestCase(root);
        return false;
    }

    std::filesystem::permissions(filePath, std::filesystem::perms::owner_read, std::filesystem::perm_options::add, ec);

    auto t = std::filesystem::last_write_time(filePath, ec);
    std::filesystem::last_write_time(filePath, t, ec);

    if (std::filesystem::absolute(filePath, ec).empty() || std::filesystem::canonical(filePath, ec).empty())
    {
        cleanUpTestCase(root);
        return false;
    }

    if (!std::filesystem::equivalent(filePath, filePath, ec))
    {
        cleanUpTestCase(root);
        return false;
    }

    std::filesystem::space_info si = std::filesystem::space(root, ec);
    if (ec || si.capacity == 0)
    {
        cleanUpTestCase(root);
        return false;
    }

    if (!std::filesystem::exists(std::filesystem::temp_directory_path(), ec))
    {
        cleanUpTestCase(root);
        return false;
    }

    if (!std::filesystem::is_regular_file(filePath, ec) || !std::filesystem::is_directory(root, ec))
    {
        cleanUpTestCase(root);
        return false;
    }

    cleanUpTestCase(root);
    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_status);
}
