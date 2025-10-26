#include <testing.h>

#include <fs_tests_common/test_utils.h>

#include <filesystem>
#include <fstream>

bool test_iteration_single_file_and_nested_dir()
{
    std::error_code ec;
    STDC::Testing::FileSystemTestCase testCase("test_dir");

    const std::filesystem::path root = testCase.path();
    const std::filesystem::path nestedDir = root / "subdir/nested";
    const std::filesystem::path filePath = root / "file_renamed.txt";

    std::filesystem::create_directories(nestedDir, ec);

    std::ofstream ofs = STDC::Testing::open_stream_from_path<std::ofstream>(filePath);
    if (!ofs)
        return false;
    ofs << "test content\n";
    ofs.close();

    if (!std::filesystem::exists(root, ec) || !std::filesystem::is_directory(root, ec))
        return false;

    // Shallow iteration
    bool foundFile = false;
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(root, ec))
    {
        if (entry.path().filename() == "file_renamed.txt")
        {
            foundFile = true;
            break;
        }
    }

    if (!foundFile)
        return false;

    // Recursive iteration
    bool foundNested = false;
    for (const std::filesystem::directory_entry &entry : std::filesystem::recursive_directory_iterator(root, ec))
    {
        if (entry.path().filename() == "nested")
        {
            foundNested = true;
            break;
        }
    }

    return foundNested;
}

bool test_iteration_multiple_files_and_dirs()
{
    std::error_code ec;
    STDC::Testing::FileSystemTestCase testCase("test_dir_multi");

    const std::filesystem::path root = testCase.path();
    const std::filesystem::path dirA = root / "dirA";
    const std::filesystem::path dirB = root / "dirB";

    std::filesystem::create_directories(dirA, ec);
    std::filesystem::create_directories(dirB, ec);

    std::ofstream f1 = STDC::Testing::open_stream_from_path<std::ofstream>(root / "file1.txt");
    std::ofstream f2 = STDC::Testing::open_stream_from_path<std::ofstream>(root / "file2.txt");
    std::ofstream f3 = STDC::Testing::open_stream_from_path<std::ofstream>(dirA / "file3.txt");
    std::ofstream f4 = STDC::Testing::open_stream_from_path<std::ofstream>(dirB / "file4.txt");

    auto r = root.c_str();

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

    return fileCount == 4 && dirCount >= 2;
}

int main()
{
    PM_PRINT_COMPILE_INFO;
    PM_EXECUTE_TEST(test_iteration_single_file_and_nested_dir);
    PM_EXECUTE_TEST(test_iteration_multiple_files_and_dirs);
}
