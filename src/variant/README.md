# Implementation info

* Source: [variant-lite](https://github.com/martinmoene/variant-lite) - [ce0be8f](https://github.com/martinmoene/variant-lite/commit/ce0be8f4ea0407476209b2cb4a107f40b7a1b71b)

# Compatibility Matrix

## MSVC

### UCRT

`std::bad_variant_access`

| Version        | Required C++ standard | Header           |
|----------------|-----------------------|------------------|
| 14.44.x.x      | Any                   | `<exception>`    |
| 14.29.x.x      | 17                    | `<variant>`      |
| 14.16.x.x      | 17                    | `<variant>`      |
| 14.00.x.x      | —                     | —                |

`std::monostate`

| Version        | Required C++ standard | Header           |
|----------------|-----------------------|------------------|
| 14.44.x.x      | 17                    | `<variant>`      |
| 14.29.x.x      | 17                    | `<xutility>`     |
| 14.16.x.x      | 17                    | `<variant>`      |
| 14.00.x.x      | —                     | —                |

> **Caveat:** For some unknown reason UCRT versions heigher than 14.29 with C++17 causes the compiler to be unable to find the == operator for `std::monostate` class</br>
> specifically for such code
> ```cpp
> std::variant<std::monostate, int> variant1;
> // The compiler fails to find the appropriate declaration of 
> // `bool operatror==(std::monostate, std::monostate)`
> // When UCRT_VERSION >= 14.29 && CPP_VERSION == (C++17)
> variant1 == std::variant<std::monostate, int>(std::monostate{});
> ```
> This doesn't happen with any C++ version otherthan C++17