#include <testing.h>

#include <fs_tests_common/test_utils.h>

#include <filesystem>
#include <fstream>

// Optional feature toggles (all OFF by default unless defined externally)
//
//   - STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH   (C++17)

bool test_operations()
{
    std::error_code ec;
    STDC::Testing::FileSystemTestCase testCase("test_dir");

    const std::filesystem::path root = testCase.path();
    const std::filesystem::path filePath = root / "file.txt";
    const std::filesystem::path copyPath = root / "file_copy.txt";
    const std::filesystem::path renamedPath = root / "file_renamed.txt";
    const std::filesystem::path nestedDir = root / "subdir/nested";

    bool success = true;

    do
    {
        // Create nested directory inside root
        if (!std::filesystem::create_directories(nestedDir, ec))
        {
            success = false;
            break;
        }

        // Write to file.txt
#ifdef STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH
        std::ofstream ofs(filePath);
#else
        std::ofstream ofs(filePath.string());
#endif
        if (!ofs)
        {
            success = false;
            break;
        }
        ofs << "Hello filesystem\n";
        ofs.close();

        // Check file size
        if (std::filesystem::file_size(filePath, ec) == 0)
        {
            success = false;
            break;
        }

        // Copy file
        if (!std::filesystem::copy_file(filePath, copyPath, std::filesystem::copy_options::overwrite_existing, ec))
        {
            success = false;
            break;
        }

        // Rename copied file
        std::filesystem::rename(copyPath, renamedPath, ec);
        if (!std::filesystem::exists(renamedPath, ec))
        {
            success = false;
            break;
        }

        // Resize original file
        std::filesystem::resize_file(filePath, 5, ec);
        if (std::filesystem::file_size(filePath, ec) != 5)
        {
            success = false;
            break;
        }

    } while (false);

    return success;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_operations);
}
