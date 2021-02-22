cmake_minimum_required(VERSION 3.10)

set(FILE_SOURCES
  "main.cpp"
)
set(FILE_HEADERS
)

add_subdirectory(util)

add_executable(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE util)