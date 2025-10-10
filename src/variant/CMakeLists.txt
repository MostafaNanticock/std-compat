std_compat_add_module(variant
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/variant
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/variant.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/variant_compat.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/std-compat/internal/variant_compat_msvc.h

    DEPENDS
        StdCompat::common

    COMPILE_DEFINITIONS
        variant_CONFIG_SELECT_VARIANT=1
        variant_CONFIG_OVERRIDE_MONOSTATE=std::monostate # FIXME: for development purposes
)
