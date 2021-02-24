cmake_minimum_required(VERSION 3.10)
project(delegate VERSION 0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
  # ignore warning 4251
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif()

# platform
if (WIN32)
  add_compile_options(-DWINDOWS)
else()
  add_compile_options(-DNWINDOWS)
endif()

# root directory of all source file will be src directory.
include_directories("${CMAKE_SOURCE_DIR}/src")

add_subdirectory(src)