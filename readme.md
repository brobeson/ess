# ess

A C++ library for various types of curves.

[![Travis CI Build Status](https://travis-ci.com/brobeson/ess.svg?branch=master)](https://travis-ci.com/brobeson/ess)

[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/sq748wjywgvhwpx0?svg=true)](https://ci.appveyor.com/project/brobeson/ess)

## Building

You need [CMake](https://cmake.org/) to generate a build system for this
project. Check
[CMakeLists.txt:1](https://github.com/brobeson/ess/blob/master/CMakeLists.txt#L1)
for the minimum version needed.

When you run CMake, there is the option `quality_checks`, which is on by
default. This integrates other tools into the build process, such as clang-tidy,
clang-format, and others. If you just want to build and install the library, you
can turn this off:

```
$ cmake -D quality_checks:BOOL=off path/to/source_tree
```

If you leave the quality checks on, CMake will attempt to locate the tools on
your system. Any missing tools will generate a CMake error.

After you generate a build system with CMake, just run the build.

```
$ mkdir build
$ cd build
$ cmake -D quality_checks:BOOL=off ../source
$ cmake --build .
```
