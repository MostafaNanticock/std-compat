#include <testing.h>

#include <fs_tests_common/u8string.h>

#include <filesystem>
#include <sstream>

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

    // ---- Shim-specific tests ----
    std::filesystem::path shim1 = std::filesystem::path("shim/from_base_copy");
    std::filesystem::path shim2 = std::filesystem::path(std::filesystem::path("shim/from_base_move"));

    std::filesystem::path shim3;                   // default constructor
    std::filesystem::path shim4(shim1);            // copy constructor
    std::filesystem::path shim5(std::move(shim2)); // move constructor

    std::filesystem::path shim6;
    shim6 = shim4; // copy assignment
    std::filesystem::path shim7;
    shim7 = std::move(shim5); // move assignment

    // ---- Comparison operators ----
    bool eq = (p1 == p9);
    bool neq = (p1 != p4);
    bool lt = (p4 < p5);
    bool le = (p4 <= p5);
    bool gt = (p5 > p4);
    bool ge = (p5 >= p4);

    // ---- Concatenation and append operators ----
    std::filesystem::path concat1 = p1 / "subdir";
    std::filesystem::path concat2 = p4;
    concat2 /= "subdir";

    std::filesystem::path append1 = p5;
    append1 += ".dll";

    // ---- Stream insertion ----
    std::ostringstream oss;
    oss << p1 << " | " << p4 << " | " << concat1;

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
    pathsList.push_back(shim1);
    pathsList.push_back(shim3);
    pathsList.push_back(shim4);
    pathsList.push_back(shim5);
    pathsList.push_back(shim6);
    pathsList.push_back(shim7);
    pathsList.push_back(concat1);
    pathsList.push_back(concat2);
    pathsList.push_back(append1);

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

    return eq && !neq && lt && le && gt && ge;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_filesystem_path);
}
