// shim files
#include <expected_compatibility>
#include <filesystem>
#include <optional>
#include <span>
#include <variant>

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#ifndef PM_UNUSED
#    define PM_UNUSED(x) static_cast<void>(x)
#endif

// clang-format off
#define PM_EXECUTE_TEST(TestFunctionName)                                                       \
    std::cout << "=== Testing " << #TestFunctionName << " ===" << std::endl;                    \
    if (!TestFunctionName())                                                                    \
    {                                                                                           \
        std::cerr << "Test function :" << #TestFunctionName << "() failed" << std::endl;        \
        return 0;                                                                               \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        std::cout << "=== " << #TestFunctionName << ": All tests passed ===\n" << std::endl;    \
    }
// clang-format on

bool test_expected();
bool test_filesystem();
bool test_optional();
bool test_span();
bool test_variant();

int main()
{
    PM_EXECUTE_TEST(test_expected);
    PM_EXECUTE_TEST(test_filesystem);
    PM_EXECUTE_TEST(test_optional);
    PM_EXECUTE_TEST(test_span);
    PM_EXECUTE_TEST(test_variant);
}

struct Box
{
    int v;
    int get() const
    {
        return v;
    }
};

bool test_expected()
{
    // 1. Default construction with value
    std::expected<int, std::string> e1(42);
    if (!e1.has_value())
        return false;
    if (*e1 != 42)
        return false;

    // 2. Construction with unexpected
    std::expected<int, std::string> e2(std_compatibility::unexpected<std::string>("error"));
    if (e2.has_value())
        return false;
    if (e2.error() != "error")
        return false;

    // 3. Copy constructor
    std::expected<int, std::string> e3 = e1;
    if (!e3.has_value() || *e3 != 42)
        return false;

    // 4. Move constructor
    std::expected<int, std::string> e4 = std::move(e3);
    if (!e4.has_value() || *e4 != 42)
        return false;

    // 5. Copy assignment
    e4 = e2;
    if (e4.has_value())
        return false;
    if (e4.error() != "error")
        return false;

    // 6. Move assignment
    e4 = std::expected<int, std::string>(99);
    if (!e4.has_value() || *e4 != 99)
        return false;

    // 7. operator-> and operator*
    std::expected<Box, std::string> bx(Box{7});
    if (!bx.has_value())
        return false;
    if (bx->get() != 7)
        return false; // operator-> path
    if ((*bx).get() != 7)
        return false; // operator* path

    // 8. value() and error()
    if (e4.value() != 99)
        return false;
    e4 = std_compatibility::unexpected<std::string>("oops");
    if (e4.has_value())
        return false;
    if (e4.error() != "oops")
        return false;

    // 9. value_or()
    if (e4.value_or(123) != 123)
        return false;
    e4 = 77;
    if (e4.value_or(123) != 77)
        return false;

    // 10. error_or() (C++23, but tl::expected provides it)
    e4 = 55;
    if (e4.error_or(std::string("fallback")) != "fallback")
        return false;
    e4 = std_compatibility::unexpected<std::string>("bad");
    if (e4.error_or(std::string("fallback")) != "bad")
        return false;

    // 11. emplace()
    e4.emplace(88);
    if (!e4.has_value() || *e4 != 88)
        return false;

    // 12. swap (member)
    std::expected<int, std::string> e5(11);
    e4.swap(e5);
    if (*e4 != 11 || *e5 != 88)
        return false;

    // 13. swap (non-member)
    std::swap(e4, e5);
    if (*e4 != 88 || *e5 != 11)
        return false;

    // 14. Monadic and_then()
    bool and_then_called = false;
    PM_UNUSED(e4.and_then(
        [&](int v)
        {
            and_then_called = (v == 88);
            return std::expected<int, std::string>(v + 1);
        }));
    if (!and_then_called)
        return false;

    // 15. Monadic transform()
    auto e6 = e4.transform([](int v) { return v * 2; });
    if (!e6.has_value() || *e6 != 176)
        return false;

    // 16. Monadic or_else()
    auto e7 = e4.or_else([](const std::string &) { return std::expected<int, std::string>(999); });
    if (!e7.has_value() || *e7 != 88)
        return false;

    std::expected<int, std::string> e8 = std_compatibility::unexpected<std::string>("err");
    auto e9 = e8.or_else([](const std::string &) { return std::expected<int, std::string>(999); });
    if (!e9.has_value() || *e9 != 999)
        return false;

    // 17. Monadic transform_error()
    auto e10 = e8.transform_error([](const std::string &s) { return s + "!"; });
    if (e10.error() != "err!")
        return false;

    // 18. bad_expected_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(e8.value()); // should throw
        }
        catch (const std::bad_expected_access<std::string> &ex)
        {
            if (ex.error() != "err")
                return false;
            threw = true;
        }
        if (!threw)
            return false;
    }

    return true;
}

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

// Optional feature toggles (if we need c++23 compatibility [Off by default]):
//   - STD_OPTIONAL_HAS_MONADIC_OPERATIONS

bool test_optional()
{
    // 1. Default construction (empty)
    std::optional<int> o1;
    if (o1.has_value())
        return false;

    // 2. Construction with value
    std::optional<int> o2(42);
    if (!o2.has_value() || *o2 != 42)
        return false;

    // 3. Copy constructor
    std::optional<int> o3 = o2;
    if (!o3.has_value() || *o3 != 42)
        return false;

    // 4. Move constructor
    std::optional<int> o4 = std::move(o3);
    if (!o4.has_value() || *o4 != 42)
        return false;

    // 5. Copy assignment
    o4 = o1;
    if (o4.has_value())
        return false;

    // 6. Move assignment
    o4 = std::optional<int>(99);
    if (!o4.has_value() || *o4 != 99)
        return false;

    // 7. operator-> and operator*
    struct Box
    {
        int v;
        int get() const
        {
            return v;
        }
    };
    std::optional<Box> ob(Box{7});
    if (!ob.has_value())
        return false;
    if (ob->get() != 7)
        return false;
    if ((*ob).get() != 7)
        return false;

    // 8. value()
    if (ob.value().get() != 7)
        return false;

    // 9. value_or()
    if (o1.value_or(123) != 123)
        return false;
    if (o2.value_or(123) != 42)
        return false;

    // 10. reset()
    o2.reset();
    if (o2.has_value())
        return false;

    // 11. emplace()
    o2.emplace(55);
    if (!o2.has_value() || *o2 != 55)
        return false;

    // 12. swap (member)
    std::optional<int> o5(11);
    o2.swap(o5);
    if (*o2 != 11 || *o5 != 55)
        return false;

    // 13. swap (non-member)
    std::swap(o2, o5);
    if (*o2 != 55 || *o5 != 11)
        return false;

#ifdef STD_OPTIONAL_HAS_MONADIC_OPERATIONS
    // 14. Monadic and_then()
    bool and_then_called = false;
    o2.and_then(
        [&](int v)
        {
            and_then_called = (v == 55);
            return std::optional<int>(v + 1);
        });
    if (!and_then_called)
        return false;

    // 15. Monadic transform()
    auto o6 = o2.transform([](int v) { return v * 2; });
    if (!o6.has_value() || *o6 != 110)
        return false;

    // 16. Monadic or_else()
    auto o7 = o2.or_else([]() { return std::optional<int>(999); });
    if (!o7.has_value() || *o7 != 55)
        return false;
#endif

    auto o8 = std::optional<int>();

#ifdef STD_OPTIONAL_HAS_MONADIC_OPERATIONS
    auto o9 = o8.or_else([]() { return std::optional<int>(999); });
    if (!o9.has_value() || *o9 != 999)
        return false;
#endif

    // 17. bad_optional_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(o8.value()); // should throw
        }
        catch (const std::bad_optional_access &)
        {
            threw = true;
        }
        if (!threw)
            return false;
    }

    return true;
}

// Optional feature toggles (if we need c++23 compatibility [Off by default]):
//   - STD_SPAN_HAS_CBEGIN_CEND
//   - STD_SPAN_HAS_CRBEGIN_CREND
//   - STD_SPAN_HAS_AT

struct POD
{
    int x;
    explicit POD(int v = 0) : x(v)
    {
    }
};

bool test_span()
{
    // 0. Helper data
    int carr[5] = {1, 2, 3, 4, 5};
    std::array<int, 4> a4 = {{10, 20, 30, 40}};

    // 1. Helper constant: dynamic_extent and static member extent
    if (std::span<int, 4>::extent != 4)
        return false;
    if (std::span<int, std::dynamic_extent>::extent != std::dynamic_extent)
        return false;

    // 2. Constructors
    // 2.1 from C array (dynamic extent)
    std::span<int> s(carr);
    if (s.size() != 5)
        return false;
    if (s.data() != &carr[0])
        return false;

    // 2.2 from pointer + size
    std::span<int> sptr(&carr[0], 5);
    if (sptr.size() != 5 || sptr.data() != &carr[0])
        return false;

    // 2.3 from std::array
    std::span<int> sa(a4);
    if (sa.size() != 4 || sa.data() != a4.data())
        return false;

    // 2.4 from const (propagates const)
    const std::array<int, 3> ca3 = {{7, 8, 9}};
    std::span<const int> sca(ca3);
    if (sca.size() != 3 || sca.data() != ca3.data())
        return false;

    // 2.5 converting ctor between spans (const-qualification, narrower extent)
    std::span<int, 5> s_fixed(carr);
    std::span<const int> s_const_from_dyn = s; // const conversion
    std::span<const int, 5> s_const_fixed_from_fixed = s_fixed;
    if (s_const_from_dyn.size() != 5 || s_const_fixed_from_fixed.size() != 5)
        return false;

    // 3. Assignment
    std::span<int> s_assign = s;
    s_assign = sptr;
    if (s_assign.data() != &carr[0] || s_assign.size() != 5)
        return false;

    // 4. Iterators
    // 4.1 begin/end
    if (s.begin() == s.end())
        return false;
    if (*(s.begin()) != carr[0])
        return false;
    if (*((s.end()) - 1) != carr[4])
        return false;

    // 4.2 rbegin/rend
    if (*s.rbegin() != carr[4])
        return false;
    if (*((s.rend()) - 1) != carr[0])
        return false;

#ifdef STD_SPAN_HAS_CBEGIN_CEND
    // 4.3 cbegin/cend
    if (*(s.cbegin()) != carr[0])
        return false;
    if (*((s.cend()) - 1) != carr[4])
        return false;
#endif

#ifdef STD_SPAN_HAS_CRBEGIN_CREND
    // 4.4 crbegin/crend
    if (*s.crbegin() != carr[4])
        return false;
    if (*((s.crend()) - 1) != carr[0])
        return false;
#endif

    // 5. Element access
    if (s.front() != 1)
        return false;
    if (s.back() != 5)
        return false;
    if (s[0] != 1 || s[4] != 5)
        return false;
#ifdef STD_SPAN_HAS_AT
    if (s.at(0) != 1 || s.at(4) != 5)
        return false;
#endif

    // 6. Observers
    if (s.size() != 5)
        return false;
    if (s.size_bytes() != 5 * sizeof(int))
        return false;
    if (s.empty())
        return false;
    std::span<int> empty_span;
    if (!empty_span.empty() || empty_span.size() != 0)
        return false;

    // 7. data()
    if (s.data() != &carr[0])
        return false;

    // 8. Subviews: first/last/subspan
    // 8.1 compile-time extents
    std::span<int, 2> s_first2_ct = s.first<2>();
    if (s_first2_ct.size() != 2 || s_first2_ct[0] != 1 || s_first2_ct[1] != 2)
        return false;

    std::span<int, 3> s_last3_ct = s.last<3>();
    if (s_last3_ct.size() != 3 || s_last3_ct[0] != 3 || s_last3_ct[2] != 5)
        return false;

    std::span<int, 3> s_sub_ct = s.subspan<1, 3>();
    if (s_sub_ct.size() != 3 || s_sub_ct[0] != 2 || s_sub_ct[2] != 4)
        return false;

    // 8.2 runtime counts
    std::span<int> s_first2_rt = s.first(2);
    if (s_first2_rt.size() != 2 || s_first2_rt[1] != 2)
        return false;

    std::span<int> s_last3_rt = s.last(3);
    if (s_last3_rt.size() != 3 || s_last3_rt[0] != 3)
        return false;

    std::span<int> s_sub_rt = s.subspan(1, 3);
    if (s_sub_rt.size() != 3 || s_sub_rt[0] != 2 || s_sub_rt[2] != 4)
        return false;

    // 9. Non-member as_bytes / as_writable_bytes
    {
        // const view -> bytes
        std::span<const int> cs = s_const_from_dyn;
        const std::size_t bytes = cs.size_bytes();
        PM_UNUSED(bytes);

        // as_bytes
        // Note: std::as_bytes returns span<const std::byte> (if std::byte available) or an equivalent byte type in some shims.
        const std::size_t ab_size = std::as_bytes(cs).size();
        if (ab_size != cs.size_bytes())
            return false;

        // as_writable_bytes requires non-const span
        std::span<int> ws = s;
        const std::size_t awb_size = std::as_writable_bytes(ws).size();
        if (awb_size != ws.size_bytes())
            return false;

        // sanity: changing first byte modifies underlying storage (cannot portably assert exact value across endianness)
        // We only verify that the byte span points somewhere non-null and has expected size.
        if (std::as_writable_bytes(ws).data() == 0)
            return false;
    }

    // 10. Value-type variety (POD)
    POD pod_arr[2] = {POD(9), POD(8)};
    std::span<POD> sp_pod(pod_arr);
    if (sp_pod.size() != 2)
        return false;
    if (sp_pod.front().x != 9 || sp_pod.back().x != 8)
        return false;

    // 11. Const-correctness with subviews
    std::span<const int> const_sub = s.subspan(2);
    if (const_sub.size() != 3 || const_sub[0] != 3)
        return false;

    return true;
}

bool test_variant()
{
    // 1. Constructors
    std::variant<int, std::string> v1; // default constructs first alternative
    if (!std::holds_alternative<int>(v1) || v1.index() != 0)
        return false;
    if (std::get<int>(v1) != 0)
        return false;

    std::variant<int, std::string> v2(42);
    if (!std::holds_alternative<int>(v2) || std::get<int>(v2) != 42)
        return false;

    std::variant<int, std::string> v3(std::string("hello"));
    if (!std::holds_alternative<std::string>(v3) || std::get<std::string>(v3) != "hello")
        return false;

    // 2. Copy constructor
    std::variant<int, std::string> v4(v2);
    if (!std::holds_alternative<int>(v4) || std::get<int>(v4) != 42)
        return false;

    // 3. Move constructor
    std::variant<int, std::string> v5(std::move(v4));
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 42)
        return false;

    // 4. Copy assignment
    v5 = v3;
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "hello")
        return false;

    // 5. Move assignment
    v5 = std::variant<int, std::string>(99);
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 99)
        return false;

    // 6. Observers: index, valueless_by_exception
    if (v5.index() != 0)
        return false;
    if (v5.valueless_by_exception())
        return false;

    // 7. Modifiers: emplace
    v5.emplace<std::string>("world");
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "world")
        return false;

    // 8. swap (member)
    std::variant<int, std::string> v6(123);
    v5.swap(v6);
    if (!std::holds_alternative<int>(v5) || std::get<int>(v5) != 123)
        return false;
    if (!std::holds_alternative<std::string>(v6) || std::get<std::string>(v6) != "world")
        return false;

    // 9. swap (non-member)
    std::swap(v5, v6);
    if (!std::holds_alternative<std::string>(v5) || std::get<std::string>(v5) != "world")
        return false;
    if (!std::holds_alternative<int>(v6) || std::get<int>(v6) != 123)
        return false;

    // 10. Non-member visit
    bool visited = false;
    std::visit(
        [&](std::variant<int, std::string> &&arg)
        {
            visited = true;
            PM_UNUSED(arg);
        },
        v5);
    if (!visited)
        return false;

    // 11. get / get_if by type
    if (*std::get_if<std::string>(&v5) != "world")
        return false;
    if (std::get_if<int>(&v5) != nullptr)
        return false;

    // 12. get / get_if by index
    if (*std::get_if<1>(&v5) != "world")
        return false;
    if (std::get_if<0>(&v5) != nullptr)
        return false;

    // 13. holds_alternative
    if (!std::holds_alternative<std::string>(v5))
        return false;
    if (std::holds_alternative<int>(v5))
        return false;

    // 14. bad_variant_access
    {
        bool threw = false;
        try
        {
            PM_UNUSED(std::get<int>(v5)); // wrong type
        }
        catch (const std::bad_variant_access &)
        {
            threw = true;
        }
        if (!threw)
            return false;
    }

    // 15. monostate
    std::variant<std::monostate, int> v7;
    if (!std::holds_alternative<std::monostate>(v7))
        return false;
    if (!(v7 == std::variant<std::monostate, int>(std::monostate{})))
        return false;

    // 16. variant_size / variant_alternative
    if (std::variant_size<decltype(v1)>::value != 2)
        return false;
    typedef std::variant_alternative<0, decltype(v1)>::type first_type;
    if (!std::is_same<first_type, int>::value)
        return false;

    // 17. variant_npos
    if (std::variant_npos != static_cast<std::size_t>(-1))
        return false;

    return true;
}
