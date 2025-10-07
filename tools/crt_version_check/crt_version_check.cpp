#include "crt_detect.h"

#include <iostream>
#include <string>

int main()
{
    std::string version = std::to_string(PM_CRT_VERSION_MAJOR) + "." +
                          std::to_string(PM_CRT_VERSION_MINOR) + "." +
                          std::to_string(PM_CRT_VERSION_BUILD) + "." +
                          std::to_string(PM_CRT_VERSION_REVISION);

           // Human-readable summary
    std::cout << "Detected CRT: " << PM_CRT_NAME << "\n";
    std::cout << "Version      : " << version << "\n";

           // CMake-parsable key-value output (single-line values only)
    std::cout << "PM_CRT_NAME=" << PM_CRT_NAME << "\n";
    std::cout << "PM_CRT_VERSION_STRING=" << version << "\n";
    std::cout << "PM_CRT_VERSION_MAJOR=" << PM_CRT_VERSION_MAJOR << "\n";
    std::cout << "PM_CRT_VERSION_MINOR=" << PM_CRT_VERSION_MINOR << "\n";
    std::cout << "PM_CRT_VERSION_BUILD=" << PM_CRT_VERSION_BUILD << "\n";
    std::cout << "PM_CRT_VERSION_REVISION=" << PM_CRT_VERSION_REVISION << "\n";

    return 0;
}
