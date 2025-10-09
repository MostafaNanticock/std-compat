#pragma once

#include <std-compat/internal/detect_compiler.h>

// UCRT 14.44.x.x: doesn't require c++17
// UCRT 14.29.x.x: requires c++17 (defined in <variant>)
// UCRT 14.16.x.x: requires c++17 (defined in <variant>)
// UCRT 14.00.x.x: doesn't have c++17 support
#define _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_44_X_X _PM_CC_SUPPORTS_CXX17 && (PM_CRT_VERSION_MAJOR == 14) && (PM_CRT_VERSION_MINOR >= 44)
#define _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_29_X_X PM_CPP_VERSION >= 201703L && (PM_CRT_VERSION_MAJOR == 14) && (PM_CRT_VERSION_MINOR >= 29)
#define _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_16_X_X PM_CPP_VERSION >= 201703L && (PM_CRT_VERSION_MAJOR == 14) && (PM_CRT_VERSION_MINOR >= 16)
#define _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_00_X_X 0

// clang-format off
#define PM_UCRT_HAS_STD_BAD_VARIANT_ACCESS  _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_44_X_X || \
                                            _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_29_X_X || \
                                            _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_16_X_X || \
                                            _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_00_X_X

#define PM_HAS_STD_BAD_VARIANT_ACCESS_OUTSIDE_VARIANT_HEADER _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_44_X_X
// clang-format on

// UCRT 14.44.x.x: requires c++17 (defined in <variant>)
// UCRT 14.29.x.x: requires c++17 (defined in <xutility>)
// UCRT 14.16.x.x: requires c++17 (defined in <variant>)
// UCRT 14.00.x.x: doesn't have c++17 support
#define PM_HAS_STD_MONOSTATE_OUTSIDE_VARIANT_HEADER _PM_HAS_STD_BAD_VARIANT_ACCESS_UCRT_14_29_X_X
