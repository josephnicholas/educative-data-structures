include(CTest)
include(Catch)

add_library(catch_main STATIC catch_main.cc)
target_include_directories(catch_main PUBLIC ${Catch2_INCLUDES})

target_link_libraries(catch_main PUBLIC Catch2::Catch2)

add_executable(trie-test trie_test.cc)
target_include_directories(catch_main PUBLIC ${CMAKE_SOURCE_DIR}/trie)
target_link_libraries(trie-test PRIVATE catch_main)