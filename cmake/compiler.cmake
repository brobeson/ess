if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(
    compiler_options
    -fdiagnostics-show-template-tree
    -pedantic-errors
    -Walloca
    -Wcast-align=strict
    -Wcast-qual
    -Wconversion
    -Wdate-time
    -Wduplicated-branches
    -Wduplicated-cond
    -Weffc++
    -Werror
    -Wextra-semi
    -Wfloat-equal
    -Wformat=2
    -Winvalid-pch
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wnoexcept
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpedantic
    -Wplacement-new=2
    -Wredundant-decls
    -Wregister
    -Wshadow
    -Wsign-conversion
    -Wsign-promo
    -Wsubobject-linkage
    -Wswitch-default
    -Wswitch-enum
    -Wtrampolines
    -Wundef
    -Wunused
    -Wunused-macros
    -Wuseless-cast
    -Wzero-as-null-pointer-constant
    -Wall
    -Wextra
    "$<$<CONFIG:Debug>:-fstack-protector-strong -Wstack-protector>"
    "$<$<CONFIG:Debug>:-ggdb>"
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(
    compiler_options
    -fdiagnostics-show-template-tree
    -pedantic-errors
    -Weverything
    -Werror
    -Wno-c++98-c++11-c++14-compat
    -Wno-c++98-compat
    -Wno-c++11-compat
    -Wno-c++14-compat
    -Wno-documentation
    -Wno-documentation-unknown-command
    -Wno-padded
    -Wno-weak-vtables
    "$<$<CONFIG:Debug>:-fstack-protector-strong -Wstack-protector>"
    "$<$<CONFIG:Debug>:-ggdb>"
  )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(compiler_options /analyze /Wall /WX)
else()
  message(
    WARNING
    " Default compiler options are not enabled for your compiler.\n"
    " Detected CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}\n"
  )
endif()
