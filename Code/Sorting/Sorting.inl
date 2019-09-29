#ifndef DSSORTING_INL
#define DSSORTING_INL

#include <limits>

namespace DS {

#ifdef DS_DEBUG_LOG
    static int iteration = 0;
#endif // DS_DEBUG_LOG

    template <typename T>
    void printVec(std::vector<T>& vector) {
#ifdef DS_DEBUG_LOG
        std::string str;
        for (size_t index = 0; index < vector.size(); ++index) {
            str = str.append(std::to_string(vector[index])).append(", ");
        }
        X_DEBUG_COMMENT("%s", str.c_str());
#endif // DS_DEBUG_LOG
    }

    template <typename T>
    void printVecIteration(std::vector<T>& vector, int iteration) {
#ifdef DS_DEBUG_LOG
        std::string str;
        for (size_t index = 0; index < vector.size(); ++index) {
            str = str.append(std::to_string(vector[index])).append(", ");
        }
        X_DEBUG_COMMENT("%d. %s", iteration, str.c_str());
#endif // DS_DEBUG_LOG
    }

    template <typename T>
    std::size_t linearSearch(const std::vector<T>& vector, const T& val) {

#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        std::size_t found = std::numeric_limits<std::size_t>::max();

        // linearly search through the array
        for (size_t index = 0; index < vector.size(); ++index) {
#ifdef DS_DEBUG_LOG
            ++iteration;
#endif // DS_DEBUG_LOG
            if (vector[index] == val) {
                found = index;
                break;
            }
        }
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Linear search (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
        return found;
    }

    template<typename T>
    std::size_t binarySearch(const std::vector<T>& vector, const T& val)
    {
#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        std::size_t start = 0;
        std::size_t end = vector.size() - 1;
        std::size_t found = std::numeric_limits<std::size_t>::max();
        while (start != std::numeric_limits<std::size_t>::max() &&
               end != std::numeric_limits<std::size_t>::max() &&
            start <= end) {
#ifdef DS_DEBUG_LOG
            ++iteration;
#endif // DS_DEBUG_LOG

            // find the midpoint
            std::size_t mid = (start + end) / 2;

            // search midpoint
            if (vector[mid] == val) {
                found = mid;
                break;
            }
            else if (val < vector[mid]) {
                // search left sub-array [start, mid-1]
                end = mid - 1;
            }
            else {
                // search right sub-array [mid +1, end]
                start = mid + 1;
            }
        }
#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Binary search (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
        return found;
    }

    template<typename T>
    void selectionSort(std::vector<T>& vector)
    {
        // Start at index 1
        // Find the minimum element in sub array [start, end] and place it at the [index]
        // Increase start by 1 and repeat

#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        // iterate through
        for (size_t index = 0; index < vector.size(); ++index) {

            size_t min_index = index;
            // find the minimum element in the range [index + 1, end]
            for (size_t index_second = index + 1; index_second < vector.size(); ++index_second) {
                if (vector[index_second] < vector[min_index]) {
                    min_index = index_second;
                }
#ifdef DS_DEBUG_LOG
                ++iteration;
#endif // DS_DEBUG_LOG
            }

            // swap the minimum element with the current one
            std::swap(vector[index], vector[min_index]);
        }

#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Selection sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
    }

    template<typename T>
    void insertionSort(std::vector<T>& vector)
    {
#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        // Start at index 1
        // Move (and sort) the current element up to index 0, by shifting 1 position
        // Increase index and loop

        // iterate through 1 to end
        for (size_t index = 1; index < vector.size(); ++index) {

            // iteratively sort and move the current element up to index, by shifting 1 position
            // (can be done without swap)
            size_t temp_index = index;
            while (temp_index > 0 && vector[temp_index - 1] > vector[temp_index]) {
                std::swap(vector[temp_index - 1], vector[temp_index]);
                temp_index--;
#ifdef DS_DEBUG_LOG
                ++iteration;
#endif // DS_DEBUG_LOG
            }
        }

#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Insertion sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
    }

    template<typename T>
    void bubbleSort(std::vector<T>& vector)
    {
#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        // A. Iterate i from 0 to n - 1
        // B. Iterate j from 0 to n - i - 1
        //    Swap elements from [0 to n - i - 1]
        // At each end of B, the last element is sorted
        for (size_t index = 0; index < vector.size() - 1; ++index) {

            for (size_t second_index = 0; second_index < vector.size() - index - 1; ++second_index) {

                if (vector[second_index] > vector[second_index + 1]) {
                    std::swap(vector[second_index], vector[second_index + 1]);
                }
#ifdef DS_DEBUG_LOG
                ++iteration;
#endif // DS_DEBUG_LOG
            }
        }

#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Bubble sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
    }

    template<typename T>
    void mergeSortMerge(std::vector<T>& vector, size_t start, size_t mid, size_t end) {

        // copy data to two temp arrays
        size_t left_size = 1 + mid - start;
        std::vector<T> subleft(left_size);
        for (size_t i = 0; i < left_size; ++i) {
            subleft[i] = vector[start + i];
        }
        size_t right_size = end - mid;
        std::vector<T> subright(right_size);
        for (size_t i = 0; i < right_size; ++i) {
            subright[i] = vector[mid + 1 + i];
        }

        // merge the two arrays by placing smaller elements first
        size_t left_index = 0;
        size_t right_index = 0;
        for (size_t i = start; i <= end; ++i) {

            if (left_index >= left_size) {
                vector[i] = subright[right_index++];
            }
            else if (right_index >= right_size) {
                vector[i] = subleft[left_index++];
            }
            else if (subleft[left_index] <= subright[right_index]) {
                    vector[i] = subleft[left_index++];
            }
            else {
                vector[i] = subright[right_index++];
            }
        }
    }

    template<typename T>
    void mergeSortRecursive(std::vector<T>& vector, size_t start, size_t end) {

        if (start == std::numeric_limits<std::size_t>::max() || end == std::numeric_limits<std::size_t>::max()||
            start >= end) {
            return;
        }

#ifdef DS_DEBUG_LOG
        ++iteration;
#endif // DS_DEBUG_LOG

        // find the midpoint
        std::size_t mid = (start + end) / 2;

        // mergeSort the left subarray
        mergeSortRecursive(vector, start, mid);

        // mergeSort the right subarray
        mergeSortRecursive(vector, mid + 1, end);

        // merge the two subarrays
        mergeSortMerge(vector, start, mid, end);
    }

    template<typename T>
    void mergeSort(std::vector<T>& vector)
    {
#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        mergeSortRecursive(vector, 0, vector.size() - 1);

#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Merge sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
    }

    template<typename T>
    size_t quickSortChoosePivotIndex(std::vector<T>& vector, size_t start, size_t end) {
        // choose a random pivot in the range [start, end]
        size_t random = start + std::rand() % (end - start);
        // place it on the start
        std::swap(vector[random], vector[start]);
        return start;
    }

    template<typename T>
    size_t quickSortPartition(std::vector<T>& vector, size_t start, size_t end) {

        size_t pivot_index = quickSortChoosePivotIndex(vector, start, end);
        const T pivot = vector[pivot_index];

        size_t left_index = start;
        size_t right_index = end;

        while (true) {
            // move left for pivot-sorted elements
            while (vector[left_index] < pivot) {
                ++left_index;
            }
            // move right for pivot-sorted elements
            while (vector[right_index] > pivot) {
                --right_index;
            }
            // if the indices have crossed, return
            if (left_index >= right_index) {
                break;
            }

            // if the indices have not crossed, swap left and right elements
            std::swap(vector[left_index], vector[right_index]);
        }
        return right_index;
    }

    template<typename T>
    void quickSortRecursive(std::vector<T>& vector, size_t start, size_t end) {

        if (start == std::numeric_limits<std::size_t>::max() || end == std::numeric_limits<std::size_t>::max() ||
            start >= end) {
            return;
        }

#ifdef DS_DEBUG_LOG
        ++iteration;
#endif // DS_DEBUG_LOG

        size_t split_point = quickSortPartition(vector, start, end);

        // pivot-sort the left subarray
        quickSortRecursive(vector, start, split_point);

        // pivot-sort the right subarray
        quickSortRecursive(vector, split_point + 1, end);
    }

    template<typename T>
    void quickSort(std::vector<T>& vector)
    {
#ifdef DS_DEBUG_LOG
        iteration = 0;
#endif // DS_DEBUG_LOG

        quickSortRecursive(vector, 0, vector.size() - 1);

#ifdef DS_DEBUG_LOG
        X_DEBUG_COMMENT("Quick sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
    }

#include "PriorityQueue.h"
	template<typename T>
	void heapSort(std::vector<T>& vector)
	{
#ifdef DS_DEBUG_LOG
		iteration = 0;
#endif // DS_DEBUG_LOG

		DS::PriorityQueue<T, true> heap;
		heap.reserve(vector.size());
		for (auto& el : vector) {
			heap.push(el);
#ifdef DS_DEBUG_LOG
			++iteration;
#endif // DS_DEBUG_LOG
		}
		
		size_t index = 0;
		while (!heap.empty()) {
			vector[index++] = *heap.top();
			heap.pop();
#ifdef DS_DEBUG_LOG
			++iteration;
#endif // DS_DEBUG_LOG
		}

#ifdef DS_DEBUG_LOG
		++iteration;
#endif // DS_DEBUG_LOG

#ifdef DS_DEBUG_LOG
		X_DEBUG_COMMENT("Heap sort (%d items) finished after %d iterations", vector.size(), iteration);
#endif // DS_DEBUG_LOG
	}

}  // namespace DS

#endif //DSSORTING_INL
