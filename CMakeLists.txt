cmake_minimum_required(VERSION 3.12)

if(CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
  message(FATAL_ERROR "In source builds are not allowed.")
endif()

project(
  ess
  VERSION 0.0
  DESCRIPTION "A library for various types of curves."
  HOMEPAGE_URL "https://github.com/brobeson/ess"
  LANGUAGES CXX
)
include(cmake/validate_compiler.cmake)

option(
  quality_checks
  "Disabling this disables quality checks such as clang-tidy and Cppcheck."
  on
)
if(quality_checks)
  # Clang-tidy does not support concepts, so it can only be run if the compiler
  # is Clang. The code currently has a work around for Clang and concepts.
  if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    include(cmake/clang-tidy.cmake)
  endif()
endif()
include(cmake/compiler.cmake)
add_subdirectory(ess)

if(quality_checks)
  # Note, that the memory check variables must be set up before CTest is
  # included. Thus, they are here and not in the unit_tests directory.
  string(CONCAT
    MEMORYCHECK_COMMAND_OPTIONS
    "--quiet"
    " --gen-suppressions=all"
    " --tool=memcheck"
    " --leak-check=yes"
    " --track-origins=yes"
    " --error-exitcode=1"
  )
  include(CTest)
  add_subdirectory(unit_tests)
  add_subdirectory(compilation_tests)
  include(cmake/cmakelint.cmake)
endif()
