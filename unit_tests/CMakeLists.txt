# This variable controls the method of dynamic analysis to use with the unit
# tests. CMake doesn't have a built in method of ensuring a variable value is
# within an allowed set of values. So it has to be manually done here. For
# simplicity, the value is always forced to lower case.
set(
  dynamic_analysis
  "none"
  CACHE
  STRING
  "The type of dynamic analysis to build into the project."
)
set_property(
  CACHE
  dynamic_analysis
  PROPERTY
    STRINGS "none;asan;valgrind"
)
string(TOLOWER ${dynamic_analysis} analysis)
get_property(strings CACHE dynamic_analysis PROPERTY STRINGS)
if(NOT analysis IN_LIST strings)
  message(SEND_ERROR "${analysis} is not a valid value for dynamic_analysis.")
else()
  set(
    dynamic_analysis
    ${analysis}
    CACHE
    STRING
    "The type of dynamic analysis to build into the project."
  )
endif()

set(tests
  point_test
)
find_package(Boost 1.67 REQUIRED COMPONENTS unit_test_framework)
foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp)
  target_link_libraries(
    ${test}
    PRIVATE
      $<$<STREQUAL:"${dynamic_analysis}","asan">:asan>
      Boost::unit_test_framework
  )
  target_compile_definitions(${test} PRIVATE BOOST_TEST_DYN_LINK)
  add_test(NAME ${test} COMMAND ${test} --color_output=yes)
endforeach()
