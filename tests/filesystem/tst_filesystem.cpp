#include <testing.h>

#include <filesystem>

#if __cplusplus >= 201703L
#    include <string_view>
#endif

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

#ifdef STD_STRING_VIEW
#    include <string_view>
#endif

namespace stdc
{
namespace tests
{
// char8_t is only a distinct type since C++20, but we can alias to unsigned char
#if defined(__cpp_char8_t)
    using u8string = std::u8string;

    // Accept both char8_t* and char* sources
    inline u8string make_u8(const char8_t *s)
    {
        return u8string(s);
    }

    inline u8string make_u8(const char *s)
    {
        // reinterpret the byte sequence as char8_t and copy with length
        return u8string(reinterpret_cast<const char8_t *>(s), reinterpret_cast<const char8_t *>(s) + std::strlen(s));
    }
#else
    using u8string = std::basic_string<unsigned char>;

    inline u8string make_u8(const char *s)
    {
        return u8string(reinterpret_cast<const unsigned char *>(s), std::strlen(s));
    }
#endif

#ifdef STD_STRING_VIEW
    using string_view = std::string_view;
#endif

} // namespace tests
} // namespace stdc

// Optional feature toggles (all OFF by default unless defined externally)
//
//   - STD_STRING_VIEW                              (C++17)
//   - STD_CONSTRUCT_FSTREAM_FROM_FILESYSTEM_PATH   (C++17)

bool test_filesystem_path()
{
    using namespace stdc::tests;

    // ---- Constructors ----
    std::filesystem::path p1("dev/filesystem"); // const char*

    std::string s = "dev/filesystem_str";
    std::filesystem::path p2(s); // std::string

#ifdef STD_STRING_VIEW
    string_view sv = "dev/filesystem_sv";
    std::filesystem::path p3(sv); // std::string_view
#endif

    std::wstring ws = L"dev/filesystem_ws";
    std::filesystem::path p4(ws); // std::wstring

    std::u16string u16s = u"dev/filesystem_u16";
    std::filesystem::path p5(u16s); // std::u16string

    std::u32string u32s = U"dev/filesystem_u32";
    std::filesystem::path p6(u32s); // std::u32string

    stdc::tests::u8string u8s = stdc::tests::make_u8("dev/filesystem_u8");
    std::filesystem::path p7(u8s); // std::u8string (compat)

    const char *arr = "iterator_construct";
    std::filesystem::path p8(arr, arr + std::strlen(arr)); // iterator range

    std::filesystem::path p9(p1);             // copy constructor
    std::filesystem::path p10(std::move(p2)); // move constructor

    // ---- Assignment operators ----
    std::filesystem::path pa;
    pa = "assign_from_cstr"; // const char*
    pa = s;                  // std::string
#ifdef STD_STRING_VIEW
    pa = sv; // std::string_view
#endif
    pa = ws; // std::wstring
    pa = u16s;
    pa = u32s;
    pa = u8s;

    std::filesystem::path pb;
    pb = p1; // copy assignment
#ifdef STD_STRING_VIEW
    pb = std::move(p3); // move assignment
#endif

    // ---- Use them to avoid unused warnings ----
    std::vector<std::filesystem::path> pathsList;
    pathsList.push_back(p1);
    pathsList.push_back(p4);
    pathsList.push_back(p5);
    pathsList.push_back(p6);
    pathsList.push_back(p7);
    pathsList.push_back(p8);
    pathsList.push_back(p9);
    pathsList.push_back(p10);
    pathsList.push_back(pa);
    pathsList.push_back(pb);

    // ---- Additional operations ----
    std::filesystem::path p11 = "dev/filesystem";
    pathsList.push_back("dev/filesystem");

    std::filesystem::path p12;
    p12 = "dev";
    pathsList.push_back(p12.concat(".dll"));

    const char *suffix = "/subdir";
    pathsList.push_back(std::filesystem::path("dev").append(suffix, suffix + 7));

    pathsList.push_back(std::filesystem::path("file.txt").extension());
    pathsList.push_back(std::filesystem::path("/usr/bin/tool").filename());
    pathsList.push_back(std::filesystem::path("a/./b/../c").lexically_normal());
    pathsList.push_back(std::filesystem::path("/usr/bin").lexically_proximate("/usr"));
    pathsList.push_back(std::filesystem::path("/usr/bin").lexically_relative("/usr"));

    std::filesystem::path p13 = "dev/filesystem";
    pathsList.push_back(p13.make_preferred());

    pathsList.push_back(std::filesystem::path("/usr/bin/tool").parent_path());
    pathsList.push_back(std::filesystem::path("/usr/bin/tool").relative_path());

    std::filesystem::path p14 = "/usr/bin/tool";
    pathsList.push_back(p14.remove_filename());

    std::filesystem::path p15 = "file.old";
    pathsList.push_back(p15.replace_extension(".new"));

    pathsList.push_back(std::filesystem::path("/usr/bin").root_directory());
    pathsList.push_back(std::filesystem::path("C:\\Windows").root_name());
    pathsList.push_back(std::filesystem::path("C:\\Windows").root_path());
    pathsList.push_back(std::filesystem::path("file.txt").stem());

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_filesystem);
    PM_EXECUTE_TEST(test_filesystem_path);
}
