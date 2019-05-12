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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
option(
  quality_checks
  "Disabling this disables quality checks such as clang-tidy and Cppcheck."
  on
)
if(quality_checks)
  include(cmake/clang-format.cmake)
  include(cmake/clang-tidy.cmake)
  include(cmake/cppcheck.cmake)
  include(cmake/lizard.cmake)
endif()
include(cmake/compiler.cmake)

if(quality_checks)
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
  include(cmake/cmakelint.cmake)
endif()
