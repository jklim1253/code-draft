cmake_minimum_required(VERSION 3.10)
project(cre VERSION 0.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(FILE_SOURCES
  "main.cpp"
  "printer.cpp"
  "timer.cpp"
  "worker.cpp"
)
set(FILE_HEADERS
  "common.hpp"
  "printer.hpp"
  "task.hpp"
  "timer.hpp"
  "worker.hpp"
)

add_executable(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)