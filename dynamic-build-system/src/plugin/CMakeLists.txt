cmake_minimum_required(VERSION 3.10)
project(sample VERSION 0.1)

set(FILE_SOURCES
  "sample.cpp"
)
set(FILE_HEADERS
  "sample.hpp"
)

add_compile_options(-DPLUGIN_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)