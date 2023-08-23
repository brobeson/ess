# This file looks for lizard. If it is found, a build target is created to run
# lizard CCN analysis on the software.

message(STATUS "Configuring lizard CCN...")
find_program(
  lizard
  lizard
  DOC "The path to the lizard application."
)
mark_as_advanced(lizard)
if(NOT lizard)
  message(
    WARNING
    "Lizard was not found. A formatting target will not be created."
  )
  return()
endif()

# The generator expression CXX_COMPILER_ID cannot be used with a custom target,
# so the warning flag to use needs to be set the old fashioned way: with an
# if/else block.
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(warning_flag "--warning-msvs")
else()
  set(warning_flag "--warnings_only")
endif()
cmake_host_system_information(RESULT threads QUERY NUMBER_OF_LOGICAL_CORES)
add_custom_target(
  lizard
  ALL
  COMMAND
    lizard
    --CCN 10
    --length 20
    --arguments 6
    ${warning_flag}
    --working_threads ${threads}
    --modified
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
