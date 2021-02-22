cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME util)
set(MODULE_VERSION 0.1)

set(FILE_SOURCES
  "tokenize.cpp"
)
set(FILE_HEADERS
  "util.hpp"
)

add_library(${MODULE_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)