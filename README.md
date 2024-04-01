# d2

Library of auto-vectorized operations on pairs of doubles

## Features

- `thezhe::d2` - CMake library target

## Usage

```CMake
# CMakeLists.txt

include(FetchContent)
FetchContent_Declare(
    d2
    GIT_REPOSITORY https://github.com/thezhe/avec.git
    GIT_TAG <tag>
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(d2)
```

## Versioning

- Tags - stable SemVer
- `main` branch - unstable
