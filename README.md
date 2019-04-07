# Data Structures
This repo contains simple reference implementation of common C++ (using C++11) data structures and basic searching/sorting algorithms I did on my own free time and decided to upload here. It is not intended to replace or be faster than anything, just to serve as a helper on common implementations.

I tried to limit inclusion of additional header files to a minimum, e.g., only including *cstddef* and *type_traits* for basic type support, etc. Any STL headers included are required only for testing the algorithms and/or for providing some debug functionality.
One obvious limitation is the absence of any move constructor/assignment functionality that I *might* add at a later time.

# List of Files
To use a file in your own code you need to include the associated header (*.h*) and inline (*.inl*) file. Exceptions are some containers, i.e., Array, Vector, Stack, PriorityQueue, that require the base classes (listed below) as well.

Base classes:

| Name | Files | Description |
| --- | --- | --- |
| Iterators| [Iterators.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Iterators.h) | Base/Input/Output/Forward/Bidirectional/Random access iterator |
| Allocators |[Allocators.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Allocators.h) | Basic allocator functionality |

Available data structures:

| Name | Header File | Implementation File |
| --- | --- | --- |
| Array | [Array.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Array.h) | [Array.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Array.inl) |
| Vector | [Vector.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Vector.h) | [Vector.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Vector.inl) |
| Queue | [Queue.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Queue.h) | [Queue.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Queue.inl) |
| Stack | [Stack.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Stack.h) | [Stack.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/Stack.inl) |
| Linked List | [LinkedList.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/LinkedList.h) | [LinkedList.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/LinkedList.inl) |
| Double Linked List | [DoubleLinkedList.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/DoubleLinkedList.h) | [DoubleLinkedList.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/DoubleLinkedList.inl) |
| Binary Tree | [BinaryTree.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/BinaryTree.h) | [BinaryTree.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/BinaryTree.inl) |
| Binary Search Tree | [BinarySearchTree.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/BinarySearchTree.h) | [BinarySearchTree.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/BinarySearchTree.inl) |
| Priority Queue | [PriorityQueue.h](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/PriorityQueue.h) | [PriorityQueue.inl](https://github.com/kvarcg/data_structures/blob/master/Code/DataStructures/PriorityQueue.inl) |

Available searching/sorting algorithms (all in a single file):

| Name | Files |
| --- | --- |
| Linear search | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Binary search | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Selection sort | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Insertion sort | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Bubble sort | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Merge sort | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |
| Quick sort | [Sorting.h](https://github.com/kvarcg/data_structures/blob/master/Code/Sorting/Sorting.h) |

# Building the Tests or Generating VS Solution via CMake
```
mkdir build
cd build
# Windows (VS 2017)
cmake -G "Visual Studio 15 2017 Win64" ..
# MinGW 7.3
cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DCMAKE_BUILD_TYPE=Release ..
# GCC 7.3
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j<number of jobs>
```
# Running the Tests
```
make test
```
Example output:
```
$ make test
Running tests...
Test project C:/data_structures/build
      Start  1: allocators
 1/12 Test  #1: allocators .......................   Passed    0.01 sec
      Start  2: iterators
 2/12 Test  #2: iterators ........................   Passed    0.01 sec
      Start  3: array
 3/12 Test  #3: array ............................   Passed    0.01 sec
      Start  4: vector
 4/12 Test  #4: vector ...........................   Passed    0.01 sec
      Start  5: stack
 5/12 Test  #5: stack ............................   Passed    0.01 sec
      Start  6: queue
 6/12 Test  #6: queue ............................   Passed    0.01 sec
      Start  7: linkedlist
 7/12 Test  #7: linkedlist .......................   Passed    0.01 sec
      Start  8: doublelinkedlist
 8/12 Test  #8: doublelinkedlist .................   Passed    0.02 sec
      Start  9: binarytree
 9/12 Test  #9: binarytree .......................   Passed    0.01 sec
      Start 10: binarysearchtree
10/12 Test #10: binarysearchtree .................   Passed    0.01 sec
      Start 11: priorityqueue
11/12 Test #11: priorityqueue ....................   Passed    0.01 sec
      Start 12: sorting
12/12 Test #12: sorting ..........................   Passed    0.34 sec

100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.50 sec
```

# Documentation
A Doxygen file, called *Doxyfile* is included in the root folder. The generated .html files are available in the *Docs* folder.
