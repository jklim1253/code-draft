cmake_minimum_required(VERSION 3.10)
project(util VERSION 0.1)

set(FILE_SOURCES
  "tokenize.cpp"
  "executable_path.cpp"
  "printline.cpp"
)
set(FILE_HEADERS
  "util.hpp"
)

add_compile_options(-DUTIL_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)