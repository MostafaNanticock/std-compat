#include <testing.h>

#include <fs_tests_common/u8string.h>

#include <filesystem>
#include <sstream>

// Optional feature toggles (all OFF by default unless defined externally)
//
//   - STD_STRING_VIEW                              (C++17)

bool test_filesystem_path()
{
    using namespace stdc::tests;

    // ---- Constructors and assignments ----
    std::filesystem::path p1("dev/filesystem");
    std::string s = "dev/filesystem_str";
    std::filesystem::path p2(s);

#ifdef STD_STRING_VIEW
    string_view sv = "dev/filesystem_sv";
    std::filesystem::path p3(sv);
#endif

    std::wstring ws = L"dev/filesystem_ws";
    std::filesystem::path p4(ws);

    std::u16string u16s = u"dev/filesystem_u16";
    std::filesystem::path p5(u16s);

    std::u32string u32s = U"dev/filesystem_u32";
    std::filesystem::path p6(u32s);

    u8string u8s = make_u8("dev/filesystem_u8");
    std::filesystem::path p7(u8s);

    const char *arr = "iterator_construct";
    std::filesystem::path p8(arr, arr + std::strlen(arr));

    std::filesystem::path p9(p1);             // copy
    std::filesystem::path p10(std::move(p2)); // move

    std::filesystem::path pa;
    pa = "assign_from_cstr";
    pa = s;
#ifdef STD_STRING_VIEW
    pa = sv;
#endif
    pa = ws;
    pa = u16s;
    pa = u32s;
    pa = u8s;

    std::filesystem::path pb;
    pb = p1;

    // ---- Comparison checks ----
    if (!(p1 == p9))
        return false;
    if (p1 == p4)
        return false;

    // ---- Concatenation and append ----
    std::filesystem::path concat1 = p1 / "subdir";
    std::filesystem::path concat2 = p4;
    concat2 /= "subdir";

    std::filesystem::path append1 = p5;
    append1 += ".dll";

    // ---- Stream insertion ----
    std::ostringstream oss;
    oss << p1 << " | " << p4 << " | " << concat1;
    if (oss.str().empty())
        return false;

    // ---- Additional operations ----
    std::filesystem::path p12 = "dev";
    p12 += ".dll";

    const char *suffix = "/subdir";
    std::filesystem::path appended = std::filesystem::path("dev").append(suffix, suffix + 7);

    if (std::filesystem::path("file.txt").extension() != ".txt")
        return false;
    if (std::filesystem::path("/usr/bin/tool").filename() != "tool")
        return false;
    if (std::filesystem::path("a/./b/../c").lexically_normal() != "a/c")
        return false;
    if (std::filesystem::path("/usr/bin").lexically_relative("/usr") != "bin")
        return false;

    std::filesystem::path p13 = "dev/filesystem";
    p13.make_preferred(); // platform-specific

    if (std::filesystem::path("/usr/bin/tool").parent_path() != "/usr/bin")
        return false;
    if (std::filesystem::path("/usr/bin/tool").stem() != "tool")
        return false;

    std::filesystem::path p15 = "file.old";
    if (p15.replace_extension(".new").extension() != ".new")
        return false;

#ifdef _WIN32
    if (std::filesystem::path("C:\\Windows").root_name() != "C:")
        return false;
    if (std::filesystem::path("C:\\Windows").root_path() != "C:\\")
        return false;
#else
    if (std::filesystem::path("/usr/bin").root_directory() != "/")
        return false;
#endif

    return true;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_filesystem_path);
}
