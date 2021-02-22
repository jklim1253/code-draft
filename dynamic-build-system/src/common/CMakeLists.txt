cmake_minimum_required(VERSION 3.10)
project(common VERSION 0.1)

set(FILE_SOURCES
  "version.cpp"
)
set(FILE_HEADERS
  "common.hpp"
  "error_code.hpp"
  "application_code.hpp"
)

add_compile_options(-DCOMMON_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)