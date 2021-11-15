add_executable(graph graph.hpp main.cc)

message("PROJECT: ${PROJECT_SOURCE_DIR}")

target_include_directories(graph 
    PUBLIC ${CMAKE_SOURCE_DIR}/linkedlist)