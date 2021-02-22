cmake_minimum_required(VERSION 3.10)
project(util VERSION 0.1)

set(FILE_SOURCES
  "tokenize.cpp"
)
set(FILE_HEADERS
  "util.hpp"
)

add_library(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)