cmake_minimum_required(VERSION 3.10)
project(core.loader VERSION 0.1)

set(FILE_SOURCES
  "loader.cpp"
)
set(FILE_HEADERS
  "loader.hpp"
)

add_compile_options(-DCORE_LOADER_EXPORTS)

add_library(${PROJECT_NAME} SHARED
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE base)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE util)