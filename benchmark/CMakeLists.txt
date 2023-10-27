add_executable(trie_benchmark trie_benchmark.cpp)

target_include_directories(trie_benchmark
        PUBLIC ${CMAKE_SOURCE_DIR}/src/trie
        ${benchmark_INCLUDES})

target_link_libraries(trie_benchmark
        PUBLIC ${benchmark_LIBS}
        ${benchmark_SYSTEM_LIBS})

add_executable(queue_array_benchmark queue_array_benchmark.cpp)

target_include_directories(queue_array_benchmark
        PUBLIC ${CMAKE_SOURCE_DIR}/src/queue
        ${benchmark_INCLUDES})

target_link_libraries(queue_array_benchmark
        PUBLIC ${benchmark_LIBS}
        ${benchmark_SYSTEM_LIBS})
