cmake_minimum_required(VERSION 3.10)

set(FILE_SOURCES
  "main.cpp"
)
set(FILE_HEADERS
)

if (MSVC)
  # ignore warning 4251
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif()

add_subdirectory(common)
add_subdirectory(util)
add_subdirectory(base)
add_subdirectory(core)

add_executable(${PROJECT_NAME}
  ${FILE_SOURCES}
  ${FILE_HEADERS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE util)
target_link_libraries(${PROJECT_NAME} PRIVATE base)
target_link_libraries(${PROJECT_NAME} PRIVATE core.iosystem)