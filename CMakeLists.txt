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
#if(quality_checks)
#  include(cmake/clang-format.cmake)
#  include(cmake/clang-tidy.cmake)
#  include(cmake/cppcheck.cmake)
#  include(cmake/lizard.cmake)
#endif()
include(cmake/compiler.cmake)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ess::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    "${CMAKE_SOURCE_DIR}/include"
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
  AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6.1
)
  target_compile_options(${PROJECT_NAME} INTERFACE -fconcepts)
else()
  # TODO Add support for Clang and MSVC.
  message(
    FATAL_ERROR
    "Detected C++ compiler ${CMAKE_CXX_COMPILER_ID} version"
    " ${CMAKE_CXX_COMPILER_VERSION}. This compiler and version are not yet"
    " supported."
  )
endif()

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
