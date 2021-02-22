cmake_minimum_required(VERSION 3.10)
project(base VERSION 0.1)

set(FILE_SOURCES
  "isystem.cpp"
)
set(FILE_HEADERS
  "isystem.hpp"
)

add_compile_options(-DBASE_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)