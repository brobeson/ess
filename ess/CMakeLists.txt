add_library(ess INTERFACE)
add_library(ess::ess ALIAS ess)
target_include_directories(ess INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(ess INTERFACE cxx_std_17)
if(CMAKE_CXX_COMPILER_ID STREQUAL GNU
  AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 6.1
)
  target_compile_options(ess INTERFACE -fconcepts)
elseif(NOT
  (CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
)
  # TODO Add support for MSVC. See https://github.com/brobeson/ess/issues/15
  message(
    FATAL_ERROR
    "Detected C++ compiler ${CMAKE_CXX_COMPILER_ID} version"
    " ${CMAKE_CXX_COMPILER_VERSION}. This compiler and version are not yet"
    " supported."
  )
endif()
