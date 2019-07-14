# Set up compilation tests. These tests validate that code which should not
# compile, does not compile.

# Generate tests files. This simplifies adding more tests in the future. Just
# add classes or template types, and the basic C++ source file will be
# generated.
foreach(class basic_2d_point basic_3d_point basic_2d_vector basic_3d_vector)
  set(types
    bool
    char
    char16_t
    char32_t
    "int*"
    "signed char"
    std::byte
    std::string
    "unsigned char"
    wchar_t
  )
  foreach(type IN LISTS types)
    set(filename "${class}_${type}_compilation_test.cpp")
    string(REPLACE " " "_" filename ${filename})
    string(REPLACE "*" "_pointer" filename ${filename})
    string(REPLACE "std::" "" filename ${filename})
    configure_file(basic_geometry_compilation_test.in.cpp ${filename})
    get_filename_component(filename ${filename} NAME_WE)
    list(APPEND tests ${filename})
  endforeach()
endforeach()

# Set up the compiler command, based on the compiler found by CMake. All this
# command needs to do is attempt to compile a single source file to a single
# object file.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(build_command
    ${CMAKE_CXX_COMPILER}
    -fconcepts
    -std=c++2a
    -I "${CMAKE_SOURCE_DIR}/ess"
  )
else()
  # TODO Add support for Clang and MSVC.
  message(FATAL_ERROR
    "Detected C++ compiler ${CMAKE_CXX_COMPILER_ID} version"
    " ${CMAKE_CXX_COMPILER_VERSION}. This compiler and version are not yet"
    " supported."
  )
endif()

# 1. For each test source file, add a test that runs the compiler command.
# 2. Inform CTest that failure to compile is a successful test, and that
#    successful compilation is a failing test.
foreach(test IN LISTS tests)
  add_test(
    NAME ${test}
    COMMAND ${build_command} "${CMAKE_CURRENT_BINARY_DIR}/${test}.cpp"
  )
endforeach()
set_tests_properties(
  ${tests}
  PROPERTIES
    WILL_FAIL true
    LABELS compilation
)
