#pragma once

#include <filesystem>

void cleanUpTestCase(const std::filesystem::path &root)
{
    std::error_code ec;
    std::filesystem::remove_all(root, ec);
}
