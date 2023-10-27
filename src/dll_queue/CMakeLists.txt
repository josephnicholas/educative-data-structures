add_executable(dll-queue-test
        doubly_linked_list_queue.hpp
        main.cc)

target_include_directories(dll-queue-test
        PRIVATE ${CMAKE_SOURCE_DIR}/src/doubly_linkedlist)

