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
    const std::filesystem::path root = "test_dir";
    const std::filesystem::path p1 = root;
    const std::filesystem::path p2 = root / "file.txt";
    const std::filesystem::path copyPath = root / "file_copy.txt";
    const std::filesystem::path renamedPath = root / "file_renamed.txt";

    // Clean up before starting
    std::filesystem::remove_all(root, ec);

    bool success = true;

    do
    {
        if (!std::filesystem::create_directory(p1, ec) || !std::filesystem::exists(p1, ec))
        {
            success = false;
            break;
        }

        if (!std::filesystem::create_directories(root / "subdir/nested", ec))
        {
            success = false;
            break;
        }

#ifdef STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH
        std::ofstream ofs(p2);
#else
        std::ofstream ofs(p2.string());
#endif
        if (!ofs)
        {
            success = false;
            break;
        }
        ofs << "Hello filesystem\n";
        ofs.close();

        if (std::filesystem::file_size(p2, ec) == 0)
        {
            success = false;
            break;
        }

        if (!std::filesystem::copy_file(p2, copyPath, std::filesystem::copy_options::overwrite_existing, ec))
        {
            success = false;
            break;
        }

        std::filesystem::rename(copyPath, renamedPath, ec);
        if (!std::filesystem::exists(renamedPath, ec))
        {
            success = false;
            break;
        }

        std::filesystem::resize_file(p2, 5, ec);
        if (std::filesystem::file_size(p2, ec) != 5)
        {
            success = false;
            break;
        }

    } while (false);

    cleanUpTestCase(root);

    return success;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_operations);
}
