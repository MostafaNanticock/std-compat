#include <testing.h>

#include <fs_tests_common/test_utils.h>

#include <filesystem>
#include <fstream>

bool test_iteration_single_file_and_nested_dir()
{
    std::error_code ec;

    // Setup: clean and recreate test_dir structure
    std::filesystem::remove_all("test_dir", ec);
    std::filesystem::create_directories("test_dir/subdir/nested", ec);

    // Create a file to find
    std::filesystem::path filePath = "test_dir/file_renamed.txt";
    std::ofstream ofs(filePath);

    if (!ofs)
        return false;

    ofs << "test content\n";
    ofs.close();

    std::filesystem::path root = "test_dir";

    if (!std::filesystem::exists(root, ec) || !std::filesystem::is_directory(root, ec))
        return false;

    // Shallow iteration
    bool foundFile = false;
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(root, ec))
    {
        if (entry.path().filename() != "file_renamed.txt")
            continue;

        foundFile = true;
        break;
    }

    if (!foundFile)
        return false;

    // Recursive iteration
    bool foundNested = false;
    for (const std::filesystem::directory_entry &entry : std::filesystem::recursive_directory_iterator(root, ec))
    {
        if (entry.path().filename() != "nested")
            continue;

        foundNested = true;
        break;
    }

    cleanUpTestCase(root);

    return foundNested;
}

bool test_iteration_multiple_files_and_dirs()
{
    std::error_code ec;

    // Setup: clean and recreate test_dir_multi structure
    std::filesystem::remove_all("test_dir_multi", ec);
    std::filesystem::create_directories("test_dir_multi/dirA", ec);
    std::filesystem::create_directories("test_dir_multi/dirB", ec);

    // Create multiple files
    std::ofstream f1("test_dir_multi/file1.txt");
    std::ofstream f2("test_dir_multi/file2.txt");
    std::ofstream f3("test_dir_multi/dirA/file3.txt");
    std::ofstream f4("test_dir_multi/dirB/file4.txt");

    if (!f1 || !f2 || !f3 || !f4)
        return false;

    f1 << "file1\n";
    f2 << "file2\n";
    f3 << "file3\n";
    f4 << "file4\n";
    f1.close();
    f2.close();
    f3.close();
    f4.close();

    std::filesystem::path root = "test_dir_multi";

    if (!std::filesystem::exists(root, ec) || !std::filesystem::is_directory(root, ec))
        return false;

    int fileCount = 0;
    int dirCount = 0;

    for (const std::filesystem::directory_entry &entry : std::filesystem::recursive_directory_iterator(root, ec))
    {
        if (entry.is_regular_file(ec))
            ++fileCount;

        else if (entry.is_directory(ec))
            ++dirCount;
    }

    cleanUpTestCase(root);

    // Expecting 4 files and at least 2 subdirectories
    return fileCount == 4 && dirCount >= 2;
}

int main()
{
    PM_PRINT_COMPILE_INFO;
    PM_EXECUTE_TEST(test_iteration_single_file_and_nested_dir);
    PM_EXECUTE_TEST(test_iteration_multiple_files_and_dirs);
}
