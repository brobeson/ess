# This file looks for the correct version of clang-format. If it is found, a
# build target is created to run clang-format on the software.

message(STATUS "Configuring clang-format.")
find_program(
  clang_format
  clang-format
  DOC "The path to the clang-format application."
)
mark_as_advanced(clang_format)
if(NOT clang_format)
  message(
    AUTHOR_WARNING
    "Clang-format was not found. A formatting target will not be created."
  )
  return()
endif()

# A specific version of clang-format is required. In my experience, using a
# different version can wildly change the formatting.
execute_process(
  COMMAND ${clang_format} -version
  OUTPUT_VARIABLE clang_format_version
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(
  REGEX MATCH
  "[0-9]+\.[0-9]+\.[0-9]"
  clang_format_version
  "${clang_format_version}"
)
set(required_version "8.0.0")
if(NOT clang_format_version VERSION_EQUAL ${required_version})
  message(
    AUTHOR_WARNING
    "Your clang-format version is ${clang_format_version}. Version"
    " ${required_version} exactly is required. A formatting target will not be"
    " created."
  )
  set(
    clang_format
    "clang_format-NOTFOUND"
    CACHE
    FILEPATH
    "The path to the clang-format application."
    FORCE
  )
  return()
endif()

add_custom_target(
  clang-format
  ALL
  COMMAND find . -name '*.h' -exec ${clang_format} -i {} \\\;
  COMMAND find . -name '*.cpp' -exec ${clang_format} -i {} \\\;
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
