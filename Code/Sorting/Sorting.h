#ifndef DSSORTING_H
#define DSSORTING_H

#pragma once
//using namespace

// includes ////////////////////////////////////////


// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

#include <vector>

namespace DS {

    /// @brief Searches for an element linearly O(N)
    /// @param vector the vector to sort
    /// @param val the value to search
    /// @return the index of the value, max size_t otherwise
    template <typename T>
    std::size_t linearSearch(const std::vector<T>& vector, const T& val);

    /// @brief Searches for an element linearly O(logN)
    /// @param vector the vector to sort
    /// @param val the value to search
    /// @return the index of the value, max size_t otherwise
    template <typename T>
    std::size_t binarySearch(const std::vector<T>& vector, const T& val);

    /// @brief Selection sort
    /// Offline algorithm (it needs the entire list)
    /// Space Complexity: O(N), in-place
    /// Time Complexity: O(N^2), Best/Average/Worst
    /// Makes max O(N) swaps, good for memory
    /// In each iteration, it finds the smallest element in an unsorted sublist and swaps it with the current most left element:
    /// 1. Start at index 1
    /// 2. Loop and find the minimum element between index and [index, end]
    /// 3. Increase index and repeat 2 until reaching the end
    /// @param vector the vector to sort
    template <typename T>
    void selectionSort(std::vector<T>& vector);

    /// @brief Insertion sort
    /// Online (builds partial sorted lists)
    /// Space Complexity: O(N), in-place
    /// Time Complexity:
    /// Best: O(N) and O(1) swaps (sorted list)
    /// Average: O(N^2) and swaps
    /// Worse: O(N^2) and swaps (reverse list)
    /// In each iteration, it builds sorted sublists on its left by checking the current values against the values in its left. Then, it finds the correct sorted position
    /// and places the sorted element there.
    /// 1. Start at index 1
    /// 2. Compare all elements on the left up to index 0 and place the sorted element there.
    /// 3. Increase index and repeat 2 until reaching the end
    /// @param vector the vector to sort
    template <typename T>
    void insertionSort(std::vector<T>& vector);

    /// @brief Bubble sort
    /// Offline algorithm (it needs the entire list)
    /// Space Complexity: O(N), in-place
    /// Time Complexity:
    /// Best: O(N) and O(1) swaps (sorted list)
    /// Average: O(N^2) and swaps
    /// Worse: O(N^2) and swaps (reverse list)
    /// In each iteration, it compares all adjacent elements and swaps them if needed. At the end of each iteration, the right-most element is sorted. This is repeated until all elements have been sorted
    /// 1. Start iteration 1 at index1 0 to end
    /// 2. Start iteration 2 at index2 0 to end - index1
    /// 3. Compare adjacent elements and swap.
    /// 4. Loop
    /// @param vector the vector to sort
    template <typename T>
    void bubbleSort(std::vector<T>& vector);

    /// @brief Merge sort
    /// Offline algorithm (it needs the entire list)
    /// Space Complexity: O(N), O(N) auxillary
    /// Time Complexity: O(NlogN), Best/Average/Worst
    /// Divide the unsorted elements into sublists until reaching size of 1 element. Then, merge and sort each small list until reaching the original size.
    /// 1. Subdivide until lists of 1 element
    /// 2. Merge and sort until reaching the original size
    /// @param vector the vector to sort
    template <typename T>
    void mergeSort(std::vector<T>& vector);

    /// @brief Quick sort (using Hoare's variant with random pivot selection)
    /// Offline algorithm (it needs the entire list)
    /// Space Complexity: O(logN), worst case is 0(N)
    /// Time Complexity:
    /// Best: O(NlogN) and O(1) swaps (sorted list)
    /// Average: O(NlogN)
    /// Worse: O(N^2) (for sorted input)
    /// 1. Choose a pivot element in the range [start, end]
    /// 2. Sort the elements against the pivot
    /// 3. Using the obtained (and maybe moved) pivot from last iteration
    ///    loop (steps 1,2) on sublists in the range [start, pivot], [pivot+1, end] until the list is sorted
    /// @param vector the vector to sort
    template <typename T>
	void quickSort(std::vector<T>& vector);

	/// @brief Heap sort
	/// Offline algorithm (it needs the entire list)
	/// Space Complexity: O(N), in-place
	/// Time Complexity:
	/// Best: O(N+NlogN) (distinct keys) or O(N) (equal keys)
	/// Average: O(N+NlogN)
	/// Worse: O(N+NlogN)
	/// 1. Build a min heap of the elements
	/// 2. Pop all elements from the heap and add them to the array
	/// @param vector the vector to sort
	template <typename T>
	void quickSort(std::vector<T>& vector);

}  // namespace DS

#include "Sorting.inl"

#endif //DSSORTING_H_H
