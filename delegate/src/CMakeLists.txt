cmake_minimum_required(VERSION 3.10)

set(FILE_SOURCES
  "main.cpp"
  "sample.cpp"
)
set(FILE_HEADERS
  "delegate/delegate.hpp"
)

add_executable(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)