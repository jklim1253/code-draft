cmake_minimum_required(VERSION 3.10)
project(core)

add_compile_options(-DCORE_EXPORTS)

add_subdirectory(loader)
add_subdirectory(iosystem)
