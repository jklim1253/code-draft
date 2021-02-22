cmake_minimum_required(VERSION 3.10)
project(core.iosystem VERSION 0.1)

set(FILE_SOURCES
  "iosystem.cpp"
)
set(FILE_HEADERS
  "iosystem.hpp"
)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE base)