cmake_minimum_required(VERSION 3.25)
project(data-structures CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# from Jason Turner's CMake starter template
include(cmake/CompilerWarnings.cmake)
include(cmake/Conan.cmake)

# download external dependencies
run_conan()

# link dependency
find_package(Catch2 REQUIRED)
find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

#set_project_warnings(${PROJECT_NAME})

add_subdirectory(src/graph)
add_subdirectory(src/trie)
add_subdirectory(src/stack)
add_subdirectory(src/queue)
add_subdirectory(src/circular_queue)
add_subdirectory(src/heap)
add_subdirectory(src/hash_table)
add_subdirectory(test)
add_subdirectory(benchmark)
