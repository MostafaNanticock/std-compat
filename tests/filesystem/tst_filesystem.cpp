#include <../common/testing.h>

#include <filesystem>

// Optional feature toggles (for c++17 [Off by default]):
//   - STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH

bool test_filesystem()
{
    try
    {
        std::filesystem::remove_all("test_dir");

        std::filesystem::path p1{"test_dir"};
        std::filesystem::path p2{"test_dir/file.txt"};

        if (!std::filesystem::create_directory(p1) || !std::filesystem::exists(p1))
            return false;

        if (!std::filesystem::create_directories("test_dir/subdir/nested"))
            return false;

        {
#ifdef STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH
            std::ofstream ofs(p2);
#else
            std::ofstream ofs(p2.string());
#endif
            if (!ofs)
                return false;

            ofs << "Hello filesystem\n";
        }

        if (std::filesystem::file_size(p2) == 0)
            return false;

        if (!std::filesystem::copy_file(p2, "test_dir/file_copy.txt", std::filesystem::copy_options::overwrite_existing))
            return false;

        {
            bool found = false;
            for (auto &entry : std::filesystem::directory_iterator(p1))
                if (entry.path().filename() == "file_copy.txt")
                    found = true;
            if (!found)
                return false;
        }

        {
            bool foundNested = false;
            for (auto &entry : std::filesystem::recursive_directory_iterator(p1))
                if (entry.path().filename() == "nested")
                    foundNested = true;
            if (!foundNested)
                return false;
        }

        std::filesystem::file_status st = std::filesystem::status(p2);
        if (!std::filesystem::is_regular_file(st))
            return false;

        std::filesystem::permissions(p2, std::filesystem::perms::owner_read, std::filesystem::perm_options::add);

        auto t = std::filesystem::last_write_time(p2);
        std::filesystem::last_write_time(p2, t);

        if (std::filesystem::absolute(p2).empty() || std::filesystem::canonical(p2).empty())
            return false;

        PM_UNUSED(std::filesystem::relative(p2, p1));
        PM_UNUSED(std::filesystem::proximate(p2, p1));

        if (!std::filesystem::equivalent(p2, p2))
            return false;

        PM_UNUSED(std::filesystem::hard_link_count(p2));

        std::filesystem::space_info si = std::filesystem::space(p1);
        if (si.capacity == 0)
            return false;

        if (!std::filesystem::exists(std::filesystem::temp_directory_path()))
            return false;

        if (!std::filesystem::is_regular_file(p2) || !std::filesystem::is_directory(p1))
            return false;
        PM_UNUSED(std::filesystem::is_empty(p1));
        PM_UNUSED(std::filesystem::status_known(std::filesystem::status(p2)));

        try
        {
            std::filesystem::create_symlink(p2, "test_dir/link_to_file");
            if (std::filesystem::read_symlink("test_dir/link_to_file") != p2)
                std::cout << "Reading symlink failed - skipping\n";
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cout << "Symlink creation failed: " << e.what() << std::endl;
        }

        std::filesystem::rename("test_dir/file_copy.txt", "test_dir/file_renamed.txt");
        if (!std::filesystem::exists("test_dir/file_renamed.txt"))
            return false;

        std::filesystem::resize_file(p2, 5);
        if (std::filesystem::file_size(p2) != 5)
            return false;

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
    PM_EXECUTE_TEST(test_filesystem);
}
