#include <testing.h>

#include <filesystem>

bool test_error_handling()
{
    try
    {
        std::filesystem::create_symlink("test_dir/file.txt", "test_dir/link_to_file");
        if (std::filesystem::read_symlink("test_dir/link_to_file") != std::filesystem::path("test_dir/file.txt"))
        {
            std::cout << "Reading symlink failed - skipping\n";
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cout << "Symlink creation failed: " << e.what() << std::endl;
    }

    try
    {
        std::filesystem::remove("test_dir/file_renamed.txt");
        std::filesystem::remove_all("test_dir");
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
        return false;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return false;
    }

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_error_handling);
}
