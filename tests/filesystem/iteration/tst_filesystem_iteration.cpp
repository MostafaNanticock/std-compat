#include <testing.h>

#include <filesystem>

bool test_iteration()
{
    std::filesystem::path p1{"test_dir"};

    bool found = false;
    for (auto &entry : std::filesystem::directory_iterator(p1))
    {
        if (entry.path().filename() == "file_renamed.txt")
        {
            found = true;
            break;
        }
    }
    if (!found)
        return false;

    bool foundNested = false;
    for (auto &entry : std::filesystem::recursive_directory_iterator(p1))
    {
        if (entry.path().filename() == "nested")
        {
            foundNested = true;
            break;
        }
    }

    return foundNested;
}

int main()
{
    PM_PRINT_COMPILE_INFO;

    PM_EXECUTE_TEST(test_iteration);
}
