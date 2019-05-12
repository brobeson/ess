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

add_library(${PROJECT_NAME} INTERFACE)
add_library(ess::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    "${CMAKE_SOURCE_DIR}/include"
)

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
