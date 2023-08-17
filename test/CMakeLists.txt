enable_testing()

include(CTest)
include(Catch)
include(GoogleTest)

add_library(catch_main STATIC catch_main.cc)
target_include_directories(catch_main PUBLIC ${Catch2_INCLUDES})

target_link_libraries(catch_main PUBLIC Catch2::Catch2)

add_executable(trie-test trie_test.cc)
target_include_directories(catch_main
        PUBLIC ${CMAKE_SOURCE_DIR}/src/trie)
target_link_libraries(trie-test
        PRIVATE catch_main)

message(STATUS "${GTest_INCLUDE_DIRS} - ${GTest_LIBRARIES}")

add_executable(graph-test graph_test.cc)
target_include_directories(graph-test
        PUBLIC ${CMAKE_SOURCE_DIR}/src/graph
        ${CMAKE_SOURCE_DIR}/src/linkedlist
        ${GTest_INCLUDE_DIRS})
target_link_libraries(graph-test PUBLIC
        ${GTest_LIBRARIES})

add_executable(linkedlist-test linkedlist_test.cc)
target_include_directories(linkedlist-test
        PUBLIC ${CMAKE_SOURCE_DIR}/src/linkedlist
        ${GTest_INCLUDE_DIRS})
target_link_libraries(linkedlist-test
        PUBLIC ${GTest_LIBRARIES})

add_executable(doubly-linkedlist-test doubly_linkedlist_test.cc)
target_include_directories(doubly-linkedlist-test
        PUBLIC ${CMAKE_SOURCE_DIR}/src/doubly_linkedlist
        ${GTest_INCLUDE_DIRS})
target_link_libraries(doubly-linkedlist-test
        PUBLIC ${GTest_LIBRARIES})

add_executable(bst-test bst_test.cc)
target_include_directories(bst-test
        PUBLIC ${CMAKE_SOURCE_DIR}/src/binary_search_tree
        ${GTest_INCLUDE_DIRS})
target_link_libraries(bst-test
        PUBLIC ${GTest_LIBRARIES}
        ${GTest_SYSTEM_LIBRARIES})

gtest_discover_tests(doubly-linkedlist-test linkedlist-test graph-test bst-test)