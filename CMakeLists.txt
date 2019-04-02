cmake_minimum_required(VERSION 3.12)

if(CMAKE_BINARY_DIR MATCHES "${CMAKE_SOURCE_DIR}.*")
  message(FATAL_ERROR "In source builds are not allowed.")
endif()

project(
  curvy
  VERSION 0.0
  DESCRIPTION "A library for various types of curves."
  HOMEPAGE_URL "https://github.com/brobeson/curvy"
  LANGUAGES CXX
)

include(cmake/clang-format.cmake)
