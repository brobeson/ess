if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.4)
    message(FATAL_ERROR
      "GCC version ${CMAKE_CXX_COMPILER_VERSION} is not supported. The minimum"
      " officially supported version of GCC is 7.4."
    )
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.1)
    message(FATAL_ERROR
      "Clang version ${CMAKE_CXX_COMPILER_VERSION} is not supported. The"
      " minimum officially supported version of Clang is 7.1."
    )
  endif()
else()
  # TODO Add support for MSVC. See https://github.com/brobeson/ess/issues/15
  message(FATAL_ERROR
    "${CMAKE_CXX_COMPILER_ID} is not supported. At this time, only GCC and"
    " Clang are supported."
  )
endif()
