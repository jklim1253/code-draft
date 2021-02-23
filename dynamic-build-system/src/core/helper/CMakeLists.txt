cmake_minimum_required(VERSION 3.10)
project(core.helper VERSION 0.1)

set(FILE_SOURCES
  "helper.cpp"
)
set(FILE_HEADERS
  "helper.hpp"
)

add_compile_options(-DCORE_HELPER_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)