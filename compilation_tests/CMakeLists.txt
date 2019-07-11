# Set up compilation tests. These tests validate that code which should not
# compile, does not compile.
#
# 1. Set up the compiler command, based on the compiler found by CMake. All this
#    command needs to do is attempt to compile a single source file to a single
#    object file.
# 2. For each test source file, add a test that runs the compiler command.
# 3. Inform CTest that failure to compile is a successful test, and that
#    successful compilation is a failing test.

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(build_command
    ${CMAKE_CXX_COMPILER}
    -fconcepts
    -std=c++2a
    -I "${CMAKE_SOURCE_DIR}"
  )
else()
  # TODO Add support for Clang and MSVC.
  message(FATAL_ERROR
    "Detected C++ compiler ${CMAKE_CXX_COMPILER_ID} version"
    " ${CMAKE_CXX_COMPILER_VERSION}. This compiler and version are not yet"
    " supported."
  )
endif()
set(tests
  point_bool_compilation_test
)
foreach(test IN LISTS tests)
  add_test(
    NAME ${test}
    COMMAND ${build_command} "${CMAKE_CURRENT_SOURCE_DIR}/${test}.cpp"
  )
endforeach()
set_tests_properties(
  ${tests}
  PROPERTIES
    WILL_FAIL true
    LABELS compilation
)
