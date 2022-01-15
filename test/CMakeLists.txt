include(CTest)
include(Catch)

add_library(catch_main STATIC catch_main.cc)
target_include_directories(catch_main PUBLIC ${Catch2_INCLUDES})

target_link_libraries(catch_main PUBLIC Catch2::Catch2)

add_executable(trie-test trie_test.cc)
target_include_directories(catch_main PUBLIC ${CMAKE_SOURCE_DIR}/trie)
target_link_libraries(trie-test PRIVATE catch_main)

message(STATUS "${GTest_INCLUDES} - ${GTest_SYSTEM_LIBS}")
add_executable(graph-test graph_test.cc)
target_include_directories(graph-test
        PUBLIC ${CMAKE_SOURCE_DIR}/graph
        ${CMAKE_SOURCE_DIR}/linkedlist
        ${GTest_INCLUDES})
target_link_libraries(graph-test PUBLIC ${GTest_LIBS} ${GTest_SYSTEM_LIBS})
