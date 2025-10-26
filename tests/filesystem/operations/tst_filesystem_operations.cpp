#include <testing.h>

#include <filesystem>
#include <fstream>

// Optional feature toggles (all OFF by default unless defined externally)
//
//   - STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH   (C++17)

bool test_operations()
{
    std::filesystem::remove_all("test_dir");

    std::filesystem::path p1{"test_dir"};
    std::filesystem::path p2{"test_dir/file.txt"};

    if (!std::filesystem::create_directory(p1) || !std::filesystem::exists(p1))
        return false;
    if (!std::filesystem::create_directories("test_dir/subdir/nested"))
        return false;

#ifdef STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH
    std::ofstream ofs(p2);
#else
    std::ofstream ofs(p2.string());
#endif
    if (!ofs)
        return false;
    ofs << "Hello filesystem\n";

    if (std::filesystem::file_size(p2) == 0)
        return false;
    if (!std::filesystem::copy_file(p2, "test_dir/file_copy.txt", std::filesystem::copy_options::overwrite_existing))
        return false;

    std::filesystem::rename("test_dir/file_copy.txt", "test_dir/file_renamed.txt");
    if (!std::filesystem::exists("test_dir/file_renamed.txt"))
        return false;

    std::filesystem::resize_file(p2, 5);
    if (std::filesystem::file_size(p2) != 5)
        return false;

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_operations);
}
