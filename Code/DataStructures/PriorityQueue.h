#ifndef DSPRIORITYQUEUE_H
#define DSPRIORITYQUEUE_H

// includes ////////////////////////////////////////
#include <cstddef>
#include "Allocators.h"
#ifdef DS_DEBUG_LOG
#include <vector>
#endif

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {

    /// @brief Implements a priority queue based on a binary-heap
    /// Characteristics:
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Access top: O(1)
    /// - Insert: O(logn) through heapify
    /// - Delete: O(logn) through heapify
    ///
    /// @tparam T the data type of the elements
    template <typename T, bool isMin = true>
    class PriorityQueue {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type & ;
        using const_reference = const value_type&;
        using pointer = value_type * ;
        using const_pointer = const value_type*;
        using allocator = AllocatorSimple<value_type>;

    protected:
        /// @brief Internal implementation of the container
        struct PriorityQueueImpl {
            /// @brief Data container
            T *m_data = { nullptr };
            /// @brief Size of the container
            size_type m_size = { 0 };
            /// @brief Capacity of the container
            size_type m_capacity = { 0 };
        };

        // protected variable declarations
        /// @brief Container implementation
        PriorityQueueImpl m_impl;
        /// @brief Allocator
        allocator m_allocator;

        // protected function declarations

    private:
        // private variable declarations

        // private function declarations
        /// @brief Increase the capacity of the container
        /// @param capacity the capacity to increase
        /// @param capacity the minimum increase in capacity
        /// @return the new capacity
        size_type increaseCapacity(size_type capacity, size_type min) { return capacity + 2 * capacity + min; }

        /// @brief Reallocate the container with the requested capacity
        /// @param capacity the new capacity
        void reallocate(size_type capacity);

        /// @brief Destroys the requested data
        /// @param data a pointer to the data to destroy
        /// @param size the number of elements to destroy
        void destroy(value_type* data, size_type size);

        /// @brief Clone the internal data
        /// @param newdata the object to hold the cloned data
        /// @param olddata the object to clone the data from
        void clone(PriorityQueueImpl& newdata, const PriorityQueueImpl& olddata);

        /// @brief Retrieve the parent of a child
        /// @param index the array index of the child
        /// @return the parent index
        size_type parent(size_type index) const     { return (index - 1) / 2; }

        /// @brief Retrieve the left child of a parent
        /// @param index the array index of the parent
        /// @return the left index of the child
        size_type left(size_type index)    const    { return (index * 2) + 1; }

        /// @brief Retrieve the right child of a parent
        /// @param index the array index of the parent
        /// @return the right index of the child
        size_type right(size_type index) const      { return left(index) + 1; }

        /// @brief Check if a parent has a left child
        /// @param index the array index of the parent
        /// @return a flag indicating whether the parent has a left child
        bool has_left(size_type index) const        { return left(index) < m_impl.m_size; }

        /// @brief Check if a parent has a right child
        /// @param index the array index of the parent
        /// @return a flag indicating whether the parent has a right child
        bool has_right(size_type index) const       { return right(index) < m_impl.m_size; }

        /// @brief Places a new element at the top of the tree
        /// @param index the array index of the parent
        void heapify_down(size_type index);

        /// @brief Places a new element in its ordered position in the tree
        /// @param index the array index of the element
        void heapify_up(size_type index);

        /// @brief Tests if the first element is ordered "before" the second, based on whether this is a max or min heap
        /// In min heap, first element is smaller than the second. In max heap, before means larger.
        /// @param obj1 the first element to compare
        /// @param obj2 the second element to compare
        /// @return false if a parent is not ordered "before" the child
        bool isBefore(const value_type* obj1, const value_type* obj2) const { return isMin ? *obj1 < *obj2 : *obj1 > *obj2; }

    public:

        /// @brief Default Constructor
        PriorityQueue(void) = default;
        /// @brief Explicit Constructor
        /// @param capacity the initial capacity of the queue
        explicit PriorityQueue(size_type capacity);

        /// @brief Destructor
        ~PriorityQueue(void);

        /// @brief Copy Constructor
        /// @param other the container to copy
        PriorityQueue(const PriorityQueue& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        PriorityQueue& operator=(const PriorityQueue& other);

        // public function declarations
        /// @brief Return the height of the sub-tree
        /// @return the height of the sub-tree
        size_type height(size_type index);

        /// @brief Access the top element O(1)
        /// @return the element
        value_type* top(void)                           { return m_impl.m_size > 0 ? &m_impl.m_data[0] : nullptr; }
        /// @brief Access the top element O(1)
        /// @return the element
        const value_type* top(void) const               { return m_impl.m_size > 0 ? &m_impl.m_data[0] : nullptr; }

        /// @brief Checks if the container is empty
        /// @return A flag indicating whether the container is empty
        constexpr bool empty() const noexcept           { return size() == 0; }

        /// @brief Size of the container
        /// @return Size of the container
        constexpr size_type size() const noexcept       { return m_impl.m_size; }

        /// @brief Capacity of the container
        /// @return Capacity of the container
        constexpr size_type capacity() const noexcept   { return m_impl.m_capacity; }

        /// @brief Allocate new storage
        /// @param new_cap the size of the new storage
        void reserve(size_type new_cap);

        /// @brief Shrinks the container to its size
        void shrink_to_fit();

        /// @brief Clears the container of its elements. Does not change reserved memory (capacity).
        void clear() noexcept;

        /// @brief Push a new element to the container
        /// @param value the data to insert
        void push(const value_type& value);

        /// @brief Pops an element from the container
        void pop(void);

#ifdef DS_DEBUG_LOG
        /// @brief Validates the queue, i.e., that all elements are properly ordered
        /// @param index the array index of the subtree to test
        bool validateHeap(size_type index = 0) const;

        /// @brief Print traversal of the tree in a pretty way
        /// @param node the start node
        /// @param str a string to store the result
        /// @param start_level the level of the node (should not change)
        void printPretty(size_type index, std::string& str, int level) const;
#endif// DS_DEBUG_LOG

        /// @brief Logs the container
        void print(void) const;
    };
}

#include "PriorityQueue.inl"

#endif //DSPRIORITYQUEUE_H
