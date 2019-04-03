set(tests
  point_test
)

find_package(Boost 1.67 REQUIRED COMPONENTS unit_test_framework)
foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp)
  target_link_libraries(${test} PRIVATE Boost::unit_test_framework)
  target_compile_definitions(${test} PRIVATE BOOST_TEST_DYN_LINK)
  add_test(NAME ${test} COMMAND ${test} --color_output=yes)
endforeach()
