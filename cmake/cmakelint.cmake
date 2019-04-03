# This file looks for cmakelint. If it is found, cmakelint is run immediately.

find_program(
  cmakelint
  cmakelint
  DOC "The path to the cmakelint application."
)
mark_as_advanced(cmakelint)
if(NOT cmakelint)
  message(
    WARNING
    "Cmakelint was not found. It will not be run."
  )
  return()
endif()

message(STATUS "Running cmakelint.")
file(
  GLOB_RECURSE files
  LIST_DIRECTORIES false
  RELATIVE "${CMAKE_SOURCE_DIR}"
  "CMakeLists.txt"
  "*.cmake"
)
execute_process(
  COMMAND ${cmakelint} --spaces=2 ${files}
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  RESULT_VARIABLE result
  OUTPUT_VARIABLE stdout
  ERROR_QUIET
)
if(NOT result EQUAL 0)
  string(REGEX REPLACE "\n" "\n " stdout "${stdout}")
  message(SEND_ERROR " CMakelint found errors:\n" " ${stdout}")
endif()
