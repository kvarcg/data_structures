// global includes    //////////////////////////////
#include "Global.h"

#include "Tests/DataStructureTests.h"
#include "Sorting.h"

#include<limits>
#include<chrono>
#include<algorithm>
#include <random>

namespace DS {

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto timer_start = std::chrono::high_resolution_clock::now();
    auto timer_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span;

    void timerStart() {
        timer_start = std::chrono::high_resolution_clock::now();
    }

    void timerEnd() {
        timer_end = std::chrono::high_resolution_clock::now();
    }

    std::chrono::duration<double, std::milli> getTime() {
        return timer_end - timer_start;
    }

    void construct(std::vector<int>& vector, size_t num_elements) {
        vector.clear();
        vector.reserve(num_elements);
        for (size_t index = 0; index < num_elements; ++index) {
            vector.push_back(index);
        }
    }

    void reverse(std::vector<int>& vector, size_t num_elements) {
        vector.clear();
        vector.reserve(num_elements);
        for (size_t index = 0; index < num_elements; ++index) {
            vector.push_back(num_elements - index - 1);
        }
    }

    void generateRandomUniqueNumbers(std::vector<int>& vector, size_t num_elements) {
        construct(vector, num_elements);
        std::random_device rd;
        std::mt19937 g(rd());
        g.seed(seed);
        std::shuffle(vector.begin(), vector.end(), g);
    }

    template<typename T>
    using searchFP = size_t(*)(const std::vector<T>&, const T&);

    void testSearch(searchFP<int> fp, size_t num_elements, const std::string& name) {

        X_DEBUG_COMMENT("Base search tests");
        X_ASSERT_IF_FALSE(fp({ }, -1) == std::numeric_limits<std::size_t>::max());
        X_ASSERT_IF_FALSE(fp({ 0,1,2,3,4,5,6,7,8,9 }, -1) == std::numeric_limits<std::size_t>::max());
        X_ASSERT_IF_FALSE(fp({ 0,1,2,3,4,5,6,7,8,9 }, 0) == 0);
        X_ASSERT_IF_FALSE(fp({ 0,1,2,3,4,5,6,7,8,9 }, 5) == 5);
        X_ASSERT_IF_FALSE(fp({ 0,1,2,3,4,5,6,7,8,9 }, 9) == 9);

        X_DEBUG_COMMENT("Advanced search tests");
        std::vector<int> v;
        construct(v, num_elements);
        timerStart();
        size_t res = fp(v, v[0]);
        timerEnd();
        X_DEBUG_COMMENT("%s (first):\t\t %.2fms", name.c_str(), getTime());
        X_ASSERT_IF_FALSE(res == 0);
        timerStart();
        res = fp(v, v[num_elements-1]);
        timerEnd();
        X_ASSERT_IF_FALSE(res == num_elements - 1);
        X_DEBUG_COMMENT("%s (last):\t\t %.2fms", name.c_str(), getTime());
        timerStart();
        res = fp(v, v[num_elements/2]);
        timerEnd();
        X_ASSERT_IF_FALSE(res == num_elements / 2);
        X_DEBUG_COMMENT("%s (middle):\t\t %.2fms", name.c_str(), getTime());
        timerStart();
        res = fp(v, num_elements + 1);
        timerEnd();
        X_ASSERT_IF_FALSE(res == std::numeric_limits<std::size_t>::max());
        X_DEBUG_COMMENT("%s (Not found):\t %.2fms", name.c_str(), getTime());
    }

    template<typename T>
    using sortFP = void(*)(std::vector<T>&);

    void testSort(sortFP<int> fp, size_t num_elements, const std::string& name) {
        std::vector<int> v;
        construct(v, num_elements);
        timerStart();
        fp(v);
        timerEnd();
        std::chrono::duration<double, std::milli> time_span = timer_end - timer_start;
        X_DEBUG_COMMENT("%s (Sorted):\t %.2fms", name.c_str(), getTime());
        X_ASSERT_IF_FALSE(std::is_sorted(v.begin(), v.end()) == true);
        reverse(v, num_elements);
        timerStart();
        fp(v);
        timerEnd();
        X_DEBUG_COMMENT("%s (Reversed):\t %.2fms", name.c_str(), getTime());
        X_ASSERT_IF_FALSE(std::is_sorted(v.begin(), v.end()) == true);
        generateRandomUniqueNumbers(v, num_elements);
        timerStart();
        fp(v);
        timerEnd();
        X_DEBUG_COMMENT("%s (Random):\t %.2fms", name.c_str(), getTime());
        X_ASSERT_IF_FALSE(std::is_sorted(v.begin(), v.end()) == true);
    }

    namespace TESTS {
        void testSortings() {
            X_DEBUG_COMMENT("Started %s", __func__);
            int element_sizes[3] = { 100, 1000, 10000 };
            for (int i = 0; i < 3; ++i) {
                int element_size = element_sizes[i];
                X_DEBUG_COMMENT("Testing %d items", element_size);
                testSearch(linearSearch<int>, element_size, "Linear Search");
                testSearch(binarySearch<int>, element_size, "Binary Search");
                testSort(selectionSort<int>, element_size, "Selection Sort");
                testSort(insertionSort<int>, element_size, "Insertion Sort");
                testSort(bubbleSort<int>, element_size, "Bubble Sort");
                testSort(mergeSort<int>, element_size, "Merge Sort");
                testSort(quickSort<int>, element_size, "Quick Sort");
            }
            X_DEBUG_COMMENT("Finished %s", __func__);
        }
    }  // namespace TESTS
}  // namespace DS

int main() {
    DS::TESTS::testSortings();
    return 0;
}
