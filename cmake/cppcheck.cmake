# This file looks for Cppcheck. If it is found, Cppcheck is configured to
# run as part of the normal build process.

message(STATUS "Configuring Cppcheck.")
find_program(
  cppcheck
  cppcheck
  DOC "The path to the Cppcheck application."
)
mark_as_advanced(cppcheck)
if(NOT cppcheck)
  message(
    WARNING
    "Cppcheck was not found, so it will not be run with the build."
  )
  return()
endif()

cmake_host_system_information(RESULT threads QUERY NUMBER_OF_LOGICAL_CORES)
set(
  CMAKE_CXX_CPPCHECK
  "${cppcheck}"
  --enable=warning
  --enable=style
  --enable=information
  --error-exitcode=1
  --quiet
  -j ${threads}
  --relative-paths "${CMAKE_SOURCE_DIR}"
)

