set(PROJECT_NAME "DataStructures")
message(STATUS "Building DataStructures" )

set(INCLUDE_DIR
   "${CMAKE_SOURCE_DIR}/Code/Global"
   "${CMAKE_SOURCE_DIR}/Code/DataStructures")

file(GLOB_RECURSE include_files *.h* *.inl *.xml)
include_directories(${INCLUDE_DIR})

add_executable(test_allocators           Tests/AllocatorTests.cpp Allocators.h ${global_files})
add_executable(test_iterators            Tests/IteratorsTests.cpp Iterators.h ${global_files})
add_executable(test_array                Tests/ArrayTests.cpp Array.h Array.inl Iterators.h ${global_files})
add_executable(test_vector               Tests/VectorTests.cpp Vector.h Vector.inl Iterators.h Allocators.h ${global_files})

add_executable(test_stack                Tests/StackTests.cpp Stack.h Stack.inl Allocators.h ${global_files})
add_executable(test_queue                Tests/QueueTests.cpp Queue.h Queue.inl ${global_files})
add_executable(test_linkedlist           Tests/LinkedListTests.cpp LinkedList.h LinkedList.inl ${global_files})
add_executable(test_doublelinkedlist     Tests/DoubleLinkedListTests.cpp DoubleLinkedList.h DoubleLinkedList.inl ${global_files})
add_executable(test_binarytree           Tests/BinaryTreeTests.cpp BinaryTree.h BinaryTree.inl ${global_files})
add_executable(test_binarysearchtree     Tests/BinarySearchTreeTests.cpp BinarySearchTree.h BinarySearchTree.inl ${global_files})
add_executable(test_priorityqueue        Tests/PriorityQueueTests.cpp PriorityQueue.h PriorityQueue.inl ${global_files})

add_test(allocators       test_allocators)
add_test(iterators        test_iterators)
add_test(array            test_array)
add_test(vector           test_vector)

add_test(stack            test_stack)
add_test(queue            test_queue)
add_test(linkedlist       test_linkedlist)
add_test(doublelinkedlist test_doublelinkedlist)
add_test(binarytree       test_binarytree)

add_test(binarysearchtree test_binarysearchtree)
add_test(priorityqueue    test_priorityqueue)
