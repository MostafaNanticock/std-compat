//
// Legacy versions of the MSVC CRT can be downloaded from:
//      https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist
//
// To force MSVC to compile against a specific CRT version:
//
//   1. Download the desired redistributable (headers, libs, DLLs).
//   2. Install or extract it to a known directory (e.g. C:\CustomCRT\14.4.0.0).
//   3. Override the compiler's include and library paths to point to that directory.
//   4. Use /NODEFAULTLIB to disable default CRT linkage.
//   5. Explicitly link against the target CRT's import library (e.g. ucrtbase.lib).
//   6. Ensure the matching runtime DLL (e.g. ucrtbase.dll) is available at runtime.
//

// FIXME: Fix this relative path
#include "../../src/common/include/std-compat/internal/detect_crt.h"

#include <iostream>
#include <string>

int main()
{
    // clang-format off
    const std::string version = std::to_string(STDC_CRT_VERSION_MAJOR) + "." +
                                std::to_string(STDC_CRT_VERSION_MINOR) + "." +
                                std::to_string(STDC_CRT_VERSION_BUILD) + "." +
                                std::to_string(STDC_CRT_VERSION_REVISION);
    // clang-format on

    // Human-readable summary
    std::cout << "Detected CRT : " << STDC_CRT_NAME << "\n";
    std::cout << "Version      : " << version << "\n";

    // CMake-parsable key-value output (single-line values only)
    std::cout << "STDC_CRT_NAME=" << STDC_CRT_NAME << "\n";
    std::cout << "STDC_CRT_VERSION_STRING=" << version << "\n";
    std::cout << "STDC_CRT_VERSION_MAJOR=" << STDC_CRT_VERSION_MAJOR << "\n";
    std::cout << "STDC_CRT_VERSION_MINOR=" << STDC_CRT_VERSION_MINOR << "\n";
    std::cout << "STDC_CRT_VERSION_BUILD=" << STDC_CRT_VERSION_BUILD << "\n";
    std::cout << "STDC_CRT_VERSION_REVISION=" << STDC_CRT_VERSION_REVISION << "\n";

    return 0;
}
