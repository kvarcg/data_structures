#ifndef DSVECTOR_H
#define DSVECTOR_H

// includes ////////////////////////////////////////
#include <cstddef>
#include "Iterators.h"
#include "Allocators.h"

// defines /////////////////////////////////////////


// forward declarations ////////////////////////////


// class declarations //////////////////////////////

namespace DS {

    /// @brief Implements a dynamic array data structure
    /// Characteristics:
    /// Contiguous
    /// Space Complexity: O(n)
    /// Time Complexity:
    /// - Indexing: O(1)
    /// - Search: O(n)
    /// - Insert: O(n)
    /// - Delete: O(n)
    ///
    /// @tparam T the data type of the elements
    template <typename T>
    class Vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = RandomAccessMutableIterator<value_type>;
        using const_iterator = RandomAccessConstIterator<value_type>;
        using allocator = AllocatorSimple<value_type>;

    protected:
        /// @brief Internal implementation of the container
        struct VectorImpl {
            /// @brief Data container
            T *m_data = { nullptr };
            /// @brief Size of the container
            size_type m_size = { 0 };
            /// @brief Capacity of the container
            size_type m_capacity = { 0 };
        };

        // protected variable declarations
        /// @brief Container implementation
        VectorImpl m_impl;
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
        void clone(VectorImpl& newdata, const VectorImpl& olddata);

    public:

        /// @brief Default Constructor
        Vector(void) = default;
        /// @brief Explicit Constructor
        /// @param count the initial size and capacity of the container
        explicit Vector(size_type count);

        /// @brief Destructor
        ~Vector(void);

        /// @brief Copy Constructor
        /// @param other the container to copy
        Vector(const Vector& other);

        /// @brief Copy assignment operator
        /// @param other the container to copy assign
        Vector& operator=(const Vector& other);

        // public function declarations
        /// @brief Return a reference to the underlying data with bounds checking
        /// @param pos the position in the array
        /// @return A reference to data
        reference at(size_type pos);
        /// @brief Return a reference to the underlying data with bounds checking
        /// @param pos the position in the array
        /// @return A reference to data
        const_reference at(size_type pos) const;

        /// @brief Return a reference to the first element
        /// @return A reference to data
        reference front() noexcept                              { return m_impl.m_data[0]; }
        /// @brief Return a reference to the first element
        /// @return A reference to data
        const_reference front() const noexcept                  { return m_impl.m_data[0]; }

        /// @brief Return a reference to the last element
        /// @return A reference to data
        reference back() noexcept { return m_impl.m_data[size() - 1]; }
        /// @brief Return a reference to the last element
        /// @return A reference to data
        const_reference back() const noexcept                   { return m_impl.m_data[size() - 1]; }

        /// @brief Return a reference to the underlying data
        /// @param pos the position in the container
        /// @return A reference to data
        reference operator[](size_type pos) noexcept            { return m_impl.m_data[pos]; }
        /// @brief Return a reference to the underlying data
        /// @param pos the position in the container
        /// @return A reference to data
        const_reference operator[](size_type pos) const noexcept{ return m_impl.m_data[pos]; }

        /// @brief Return a pointer to the underlying data
        /// @return A pointer to data
        pointer data(void) noexcept { return m_impl.m_data; }
        /// @brief Return a pointer to the underlying data
        /// @return A pointer to data
        const_pointer data(void) const noexcept                 { return m_impl.m_data; }

        /// @brief Return an iterator to the beginning of the underlying data
        /// @return An iterator to the beginning of data
        iterator begin() noexcept                               { return iterator(&m_impl.m_data[0]); }
        const_iterator begin() const noexcept { return const_iterator(&m_impl.m_data[0]); }
        const_iterator cbegin() const noexcept { return const_iterator(&m_impl.m_data[0]); }

        /// @brief Return an iterator to the end of the underlying data
        /// @return An iterator to the end of data
        iterator  end() noexcept                                { return iterator(&m_impl.m_data[size()]); }
        const_iterator end() const noexcept                     { return const_iterator(&m_impl.m_data[size()]); }
        const_iterator cend() const noexcept                    { return const_iterator(&m_impl.m_data[size()]); }

        /// @brief Checks if the container is empty
        /// @return A flag indicating whether the container is empty
        constexpr bool empty() const noexcept                   { return size() == 0; }

        /// @brief Size of the container
        /// @return Size of the container
        constexpr std::size_t size() const noexcept             { return m_impl.m_size; }

        /// @brief Capacity of the container
        /// @return Capacity of the container
        constexpr std::size_t capacity() const noexcept         { return m_impl.m_capacity; }

        /// @brief Allocate new storage
        /// @param new_cap the size of the new storage
        void reserve(size_type new_cap);

        /// @brief Shrinks the container to its size
        void shrink_to_fit();

        /// @brief Clears the container of its elements. Does not change reserved memory (capacity).
        void clear() noexcept;

        /// @brief Assigns new values to the container
        /// @param count the number of values to insert
        /// @param value the data to insert
        void assign(size_type count, const T& value);

        /// @brief Insert a new element at the container
        /// @param pos the position in the container
        /// @param count the number of values to insert
        /// @param value the data to insert
        /// @return the iterator of the new position
        iterator insert(const_iterator pos, size_type count, const value_type& value);

        /// @brief Insert a new element at the container
        /// @param pos the position in the container
        /// @param value the data to insert
        /// @return the iterator of the new position
        iterator insert(const_iterator pos, const value_type& value)    { return insert(pos, 1, value); }

        /// @brief Erases the element at the requested iterator position
        /// @param pos the iterator in the remove range
        iterator erase(const_iterator pos)                              { return erase(pos, pos + 1); }

        /// @brief Erases the elements at the requested iterator range
        /// @param first the first iterator in the remove range
        /// @param last the last iterator in the remove range
        /// @return the iterator after the last removed element
        iterator erase(const_iterator first, const_iterator last);

        /// @brief Push a new element to the container
        /// @param value the data to insert
        void push_back(const value_type& value);

        /// @brief Pops an element from the container
        void pop_back(void);

        /// @brief Resize the container
        /// @param count the new size of the container
        void resize(size_type count)                                    { resize(count, value_type()); }

        /// @brief Resize the container
        /// @param count the new size of the container
        /// @param value the new size of the container
        void resize(size_type count, const value_type& value);

        /// @brief Logs the container
        void print(void) const;
    };
}

#include "Vector.inl"

#endif //DSVECTOR_H
