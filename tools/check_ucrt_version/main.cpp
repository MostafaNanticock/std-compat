#include <crtversion.h>
#include <string>
#include <iostream>

#define PM_UCRT_VER_MAJOR _VC_CRT_MAJOR_VERSION
#define PM_UCRT_VER_MINOR _VC_CRT_MINOR_VERSION
#define PM_UCRT_VER_BUILD _VC_CRT_BUILD_VERSION
#define PM_UCRT_VER_REVISION _VC_CRT_RBUILD_VERSION

inline std::string ucrtVersionString()
{
    static std::string result = std::to_string(PM_UCRT_VER_MAJOR) + "." +
                                std::to_string(PM_UCRT_VER_MINOR) + "." +
                                std::to_string(PM_UCRT_VER_BUILD) + "." +
                                std::to_string(PM_UCRT_VER_REVISION);
    return result;
}

int main()
{
    std::cout << ucrtVersionString() << std::endl;
    return 0;
}
