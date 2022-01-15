add_executable(graph graph.hpp main.cc)

target_include_directories(graph
    PRIVATE ${CMAKE_SOURCE_DIR}/linkedlist)