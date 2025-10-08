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
