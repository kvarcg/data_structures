#ifndef DSSTACK_H
#define DSSTACK_H

// includes ////////////////////////////////////////
#include <cstddef>
#include "Allocators.h"

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {
    /// @brief Implements an array-based stack
    /// Characteristics:
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Indexing: O(1)
    /// - Insert: O(1)
    /// - Delete: O(1)
    /// - Push/Pop: O(1)
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class StackArray {
    public:
        /// @brief Data type
        using value_type = T;
        /// @brief size type
        using size_type = std::size_t;
        /// @brief allocator
        using allocator = AllocatorSimple<value_type>;

    protected:
        /// @brief Internal implementation of the container
        struct StackArrayImpl {
            /// @brief Data container
            T *m_data = { nullptr };
            /// @brief Size of the container
            size_type m_size = { 0 };
            /// @brief Capacity of the container
            size_type m_capacity = { 0 };
        };

        // protected variable declarations
        /// @brief Container implementation
        StackArrayImpl m_impl;
        /// @brief Allocator
        allocator m_allocator;

        // protected function declarations

    private:
        // private variable declarations

        // private function declarations
        /// @brief Increase the capacity of the container
        /// @param capacity, the capacity to increase
        /// @param capacity, the minimum increase in capacity
        /// @return the new capacity
        size_type increaseCapacity(size_type capacity, size_type min) { return capacity + 2 * capacity + min; }

        /// @brief Reallocate the container with the requested capacity
        /// @param capacity, the new capacity
        void reallocate(size_type capacity);

        /// @brief Destroys the requested data
        /// @param data, a pointer to the data to destroy
        /// @param size, the number of elements to destroy
        void destroy(value_type* data, size_type size);

        /// @brief Clone the internal data
        /// @param newdata, the object to hold the cloned data
        /// @param olddata, the object to clone the data from
        void clone(StackArrayImpl& newdata, const StackArrayImpl& olddata);

    public:
        /// @brief Default Constructor
        StackArray() = default;
        /// @brief Explicit Constructor
        /// @param count the initial size of the container
        StackArray(size_type count);

        /// @brief Destructor
        ~StackArray();

        /// @brief Copy Constructor
        /// @param other the container to copy
        StackArray(const StackArray& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        StackArray& operator=(const StackArray& other);

        /// @brief Access the top element O(1)
        /// @return the element
        value_type* top(void)                           { return m_impl.m_size > 0 ? &m_impl.m_data[m_impl.m_size - 1] : nullptr; }
        /// @brief Access the top element O(1)
        /// @return the element
        const value_type* top(void) const               { return m_impl.m_size > 0 ? &m_impl.m_data[m_impl.m_size - 1] : nullptr; }

        /// @brief Add a new element to the front O(1)
        /// @param val the data of the new element
        void push(const T& val);

        /// @brief Pop an element from the front O(1)
        void pop(void);

        /// @brief Checks if the container is empty
        /// @return A flag indicating whether the container is empty
        constexpr bool empty() const noexcept           { return size() == 0; }

        /// @brief Size of the container
        /// @return Size of the container
        constexpr std::size_t size() const noexcept     { return m_impl.m_size; }

        /// @brief Capacity of the container
        /// @return Capacity of the container
        constexpr std::size_t capacity() const noexcept { return m_impl.m_capacity; }

        /// @brief Allocate new storage
        /// @param new_cap the size of the new storage
        void reserve(size_type new_cap);

        /// @brief Shrinks the container to its size
        void shrink_to_fit();

        /// @brief Clears the container of its elements. Does not change reserved memory (capacity).
        void clear() noexcept;

        /// @brief Logs the stack
        void print(void) const;
    };
}

#include "Stack.inl"

#endif //DSSTACK_H
