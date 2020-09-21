# TinyUtils

[![Build Status](https://dev.azure.com/arttet/arttet/_apis/build/status/arttet.utils?branchName=master)](https://dev.azure.com/arttet/arttet/_build/latest?definitionId=2&branchName=master)

A header-only library of modern C++ idioms

For example:
  * [Fast pImpl (Pointer To Implementation)](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Idioms#Pointer_To_Implementation_(pImpl))
    * Zero overhead cost implementation

```cpp
class Book final
{
public:
  std::string const& contents();
private:
  std::string contents_;
};
```

```cpp
#include <tiny_utils/fast_pimpl.h>

class Book final
{
public:
    std::string const& contents();
private:
    struct implementation;
    static int constexpr length{24};
    static int constexpr alignment{8};
    tiny_utils::fast_pimpl_t<implementation, length, alignment, false> impl_;
};
```

If we are using Microsoft C++ (MSVC), we should use `tiny_utils::length(40, 32, 24)` because `Debug` and `Release` have different values of `sizeof(Book)`.

```cpp
#include <tiny_utils/fast_pimpl.h>

class Book final
{
public:
    std::string const& contents();
private:
    struct implementation;
    static int constexpr length = tiny_utils::length(40, 32, 24);
    static int constexpr alignment{8};
    tiny_utils::fast_pimpl_t<implementation, length, alignment, false> impl_;
};
```

## Requirements

* [CMake 3.17+](shttps://cmake.org/download/)
* C++ 11
* [Git](https://git-scm.com/downloads)
* [Conan, the C / C++ Package Manager](https://conan.io/) ([Python 3](https://www.python.org/downloads/))
  * [Google Test](https://github.com/google/googletest)
* [Doxygen](https://www.doxygen.nl/index.html)

## Installation

We could build and run this project directly on your system.

* Download the source from GitHub with:

```sh
git clone https://github.com/arttet/tiny_utils.git
git clone git@github.com:arttet/tiny_utils.git
```

### Install requirements
```sh
python -m pip install --upgrade conan
```

### Install dependencies
```sh
conan install . -s build_type=RelWithDebInfo -if build --build=outdated
```

### Build
```sh
conan build . -bf=build
```
