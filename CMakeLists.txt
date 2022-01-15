cmake_minimum_required(VERSION 3.16)
project(data-structures CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# from Jason Turner's CMake starter template
include(cmake/CompilerWarnings.cmake)
include(cmake/Conan.cmake)

# download external dependencies
run_conan()

# link dependency
find_package(Catch2 REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(linkedlist)
add_subdirectory(graph)
add_subdirectory(trie)
add_subdirectory(binary_search_tree)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(heap)
add_subdirectory(hash_table)
add_subdirectory(test)
